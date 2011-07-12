#include <stdio.h>
#include "probobj.ph"
#include "model.h"

DTreeNode::DTreeNode(real require_flops)
{
	totalflop=require_flops;
	timeconstraint=1.0;
	coeff=1.0;
	sequential=NULL;
	parent=NULL;

	startstep=endstep=-1;
	totalstep=0;

	bAutoDelete=false;
}

DTreeNode::~DTreeNode()
{
	if (sequential!=NULL) delete sequential;
	POSITION pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *tmp=decomposition.GetNext(pos);
		if (tmp!=NULL && tmp->GetAutoDelete()) delete tmp;
	}
}

bool DTreeNode::SetTimeConstraint(real time)
{
	if (time<0) return false;
	timeconstraint=time;
	return true;
}

real DTreeNode::GetTimeConstraint()
{
	return timeconstraint;
}

bool DTreeNode::Try()
{
	try {
		sequential=InitProblem(totalflop/timeconstraint);
	}
	catch (paroc_exception  *e) {
		sequential=NULL;
	}
	return (sequential!=NULL);
}

bool DTreeNode::Decompose(CListDTreeNodePtr &decompose)
{
	if (decomposition.IsEmpty() || !ComputeTimeConstraints()) return false;

	POSITION pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *tmp=decomposition.GetNext(pos);
		decompose.AddTail(tmp);
	}
	return true;
}


bool DTreeNode::Init(AllocStrategy al)
{

	if (GetParent()==NULL) Clean();

//User should implement which object to be allocated here...
	if (timeconstraint<=0) return false;

	if (Try()) return true;



//Call Init child nodes....
	if (al==SMALL_FIRST)
	{
		//Now compute time constraints of sub-problem...
		if (!ComputeTimeConstraints()) return false;
		POSITION pos=decomposition.GetHeadPosition();
		while (pos!=NULL)
		{
			DTreeNode *node=decomposition.GetNext(pos);
			if (!node->Init(al)) return false;
		}
	}
	else
	{
		CListDTreeNodePtr list;
		DTreeNode *t=this;
		list.AddHead(t);
		while (!list.IsEmpty())
		{
			t=list.GetAt(list.GetHeadPosition());
			list.RemoveHead();
			if (!t->Try())
			{
				if (!t->Decompose(list)) return false;
			}
		}
	}

	if (GetParent()==NULL) return InitProbDependency();
	return true;
}

void DTreeNode::Clean()
{
	if (sequential!=NULL)
	{
		delete sequential;
		sequential=NULL;
	}
	else
	{
		POSITION pos=decomposition.GetHeadPosition();
		while (pos!=NULL)
		{
			DTreeNode *t=decomposition.GetNext(pos);
			t->Clean();
		}
	}
}

void DTreeNode::Solve()
{
	if (!ddg.IsEmpty()) return;
	if (sequential!=NULL)
	{
		sequential->Exec();
//	...Solve...
	}
	else
	{
		POSITION pos=decomposition.GetHeadPosition();
		while (pos!=NULL)
		{
			DTreeNode *t=decomposition.GetNext(pos);
			t->Solve();
		}
	}
}

bool DTreeNode::WaitFinish()
{
	return true;
}


void DTreeNode::AddChild(DTreeNode *p, bool autodelete)
{
	p->SetParent(this);
	decomposition.AddTail(p);
	p->SetAutoDelete(autodelete);
}

void DTreeNode::SetAutoDelete(bool val)
{
	bAutoDelete=val;
}

bool DTreeNode::GetAutoDelete()
{
	return bAutoDelete;
}

void DTreeNode::DependOn(DTreeNode *p)
{
	assert(p!=NULL && p->GetParent()==GetParent());
	ddg.AddTail(p);
}


real DTreeNode::GetFlops()
{
	return totalflop;
}


bool DTreeNode::SetCoeff(real mycoeff)
{
	if (mycoeff<=0 || mycoeff>1) return false;
	coeff=mycoeff;
	return true;
}

real DTreeNode::GetCoeff()
{
	return coeff;
}

CListDTreeNodePtr & DTreeNode::GetDependency()
{
	return ddg;
}

void DTreeNode::SetParent(DTreeNode *p)
{
	parent=p;
}

DTreeNode * DTreeNode::GetParent()
{
	return parent;
}

void DTreeNode::SetStartStep(int start)
{
	startstep=start;
}

int DTreeNode::GetStartStep()
{
	return startstep;
}

void DTreeNode::SetEndStep(int end)
{
	endstep=end;
}

int DTreeNode::GetEndStep()
{
	return endstep;
}

void DTreeNode::SetTotalStep(int nstep)
{
	totalstep=nstep;
}

int DTreeNode::GetTotalStep()
{
	return totalstep;
}

ProbObj *DTreeNode::InitProblem(real required_mflops)
{
	return NULL;
}

bool DTreeNode::ConstructSeqDiagram()
{
	if (decomposition.IsEmpty()) return false;

	POSITION pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *node=decomposition.GetNext(pos);
		assert(node!=NULL);
		node->SetStartStep(-1); //unmarked
		node->SetEndStep(1000000);
	}

	bool done=false;
//Now find start step of each task...
	int nstep=0;
	while (!done)
	{
		int i=-1;
		pos=decomposition.GetHeadPosition();
		done=true;
		//find all nodes that are "ready" and mark them...
		while (pos!=NULL)
		{
			DTreeNode *node=decomposition.GetNext(pos);
			if (node->GetStartStep()>=0) continue;

			CListDTreeNodePtr &dep=node->GetDependency();
			POSITION pos1=dep.GetHeadPosition();
			//check if all dependencies are marked
			bool canstart=true;
			int ns=-1;
			while (pos1!=NULL)
			{
				DTreeNode *node1=dep.GetNext(pos1);
				assert(node1!=NULL);
				int t=node1->GetStartStep();
				if (t==-1)
				{
					//no, current task can not start at this step...
					canstart=false;
					break;
				} else if (ns<t) ns=t;

			}
			if (canstart)
			{
				done=false;
				ns++;
				if (nstep<=ns) nstep=ns+1;
				node->SetStartStep(ns);
			}
		}
	}
//Now find end step of each task...

	pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{

		DTreeNode *node=decomposition.GetNext(pos);
		int e=node->GetStartStep()-1;

		CListDTreeNodePtr &dep=node->GetDependency();
		POSITION pos1=dep.GetHeadPosition();

		while (pos1!=NULL)
		{
			DTreeNode *node1=dep.GetNext(pos1);
			assert(node1!=NULL);
			int e1=node1->GetEndStep();
			if (e1>e) node1->SetEndStep(e);
		}
	}

	pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *node=decomposition.GetNext(pos);
		if (node->GetEndStep()>=nstep) node->SetEndStep(nstep-1);
		node->SetTotalStep(nstep);
	}
	return true;

}

bool DTreeNode::ComputeTimeConstraints()
{
	if (!ConstructSeqDiagram()) return false;

//Now re-generate sequential diagram into array structures...
	int ntask=decomposition.GetCount();
	if (ntask<=0) return false;

	CRealArray complexity;
	CIntArray start, end;
	int nstep=0;

	complexity.SetSize(ntask);
	start.SetSize(ntask);
	end.SetSize(ntask);

	real *tmp=complexity;
	int *startptr=start;
	int *endptr=end;

	POSITION pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *node=decomposition.GetNext(pos);
		assert(node!=NULL);
		*startptr=node->GetStartStep();
		startptr++;

		*endptr=node->GetEndStep();
		if (nstep<*endptr) nstep=*endptr;
		endptr++;

		*tmp=node->GetFlops();
		tmp++;
	}
	nstep++;

	ModelGenetic model(200,20,40);
	if (!model.Init(nstep,ntask,complexity,start,end)) return false;
	model.Solve(100000);

	CRealArray results;
	model.GetResults(results);
	assert(results.GetSize()==nstep);

	pos=decomposition.GetHeadPosition();

	real tc=GetTimeConstraint()*GetCoeff();
	assert(tc>0);
	while (pos!=NULL)
	{
		DTreeNode *node=decomposition.GetNext(pos);
		assert(node!=NULL);
		int s=node->GetStartStep();
		int e=node->GetEndStep();
		assert(e>=s && e<nstep && s>=0);
		real t=0;
		for (int j=s;j<=e;j++) t+=results[j];
		assert(t>0);
		node->SetTimeConstraint(t*tc);
	}
	return true;

}

bool DTreeNode::UpdateProbNext(ProbObj *p)
{
	if (!CreateNextDependency(p))
	{
		POSITION pos=decomposition.GetHeadPosition();
		if (pos==NULL) return false;

		while (pos!=NULL)
		{
			DTreeNode *t=decomposition.GetNext(pos);
			assert(t!=NULL);
			if (t->GetTotalStep()!=t->GetEndStep()+1) continue;
			if (!t->UpdateProbNext(p)) return false;
		}
		return true;
	}
}


bool DTreeNode::CreateNextDependency(ProbObj *next)
{
	if (sequential==NULL) return false;
	sequential->AddNext(*next);
	return true;
}

bool DTreeNode::UpdateProbDependency(DTreeNode *prev)
{
	if (sequential!=NULL) return prev->UpdateProbNext(sequential);

	POSITION pos=decomposition.GetHeadPosition();
	while (pos!=NULL)
	{
		DTreeNode *t=decomposition.GetNext(pos);
		assert(t!=NULL);

		if (t->GetStartStep()==0)
		{
			if (!t->UpdateProbDependency(prev)) return false;
		}
	}

	return true;
}

bool DTreeNode::UpdateChildDependency()
{
	if (sequential!=NULL) return true;
	POSITION pos=decomposition.GetHeadPosition();
	if (pos==NULL) return false;

	while (pos!=NULL)
	{
		DTreeNode *child=decomposition.GetNext(pos);
		assert(child!=NULL);

		if (!child->UpdateChildDependency()) return false;

		CListDTreeNodePtr &ddgchild=child->GetDependency();
		POSITION pos1=ddgchild.GetHeadPosition();
		while (pos1!=NULL)
		{
			DTreeNode *t=ddgchild.GetNext(pos1);
			assert(t!=NULL);
			if (!child->UpdateProbDependency(t)) return false;
		}
	}
	return true;
}

bool DTreeNode::InitProbDependency()
{
	if (sequential!=NULL)
	{
		POSITION pos=ddg.GetHeadPosition();
		while (pos!=NULL)
		{
			DTreeNode *t=ddg.GetNext(pos);
			assert(t!=NULL);
			if (!t->UpdateProbNext(sequential)) return false;
		}
		return true;
	}
	return UpdateChildDependency();
}














