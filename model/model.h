#include "paroc_list.h"
#include "modelgene.h"


/*
HOW TO USE THE FRAMEWORK

The user should create 2 classes of DTreeNode and PRobObj (see probobj.ph).
- Class DTreeNode is used to describe the decomposition tree and dependencies
among nodes (sequential object). For this class, the user should overwrite:
+ The constructure should have at least 3 params: input data, output data and total number of power required.

+ InitProblem(input,  output) to return the "real" problem object (derived from class ProbObj). In this method, the user should also implement the initialization of the created problem object. This method should return NULL if problem cannot be solved (out of resource)


- Class ProbObj describes how the problem is really solved (parallel object). The user should implement Solve method to really solve its represented problem. All input, output data necessarry are prior set in DTreeNode::InitProblem method.

-HOW TO BUILD AND SOLVE
+ The user creates DTreeNode-based objects. For each object, the user should provide input/output and required power.
+ The user use "AddChild", "DependOn" to establish the dependencies between nodes.
+ The user call "SetTimeConstraint" at the root
+ The user call "Init" at the root. If Init returns true, problem can be solved.
+ The user call "Solve" at the root.

*/


class DTreeNode;
parclass ProbObj;

typedef paroc_list<DTreeNode *> CListDTreeNodePtr;

enum  AllocStrategy {BIG_FIRST=0, SMALL_FIRST=1};
class DTreeNode
{
public:
	DTreeNode(real require_flops);
	~DTreeNode();


	virtual bool SetTimeConstraint(real time);
	virtual real GetTimeConstraint(); //Current time constraint of the problem

//Init the DTree...the user should call Init at root
//  which in turn will automatically call Init of child nodes
//The user should overide this method
//  if the child nodes require different input/output (e.g. data distribution)
//Function: create the problem or compute time constraints on child nodes and create subtitution problems
	virtual bool Init(AllocStrategy al=SMALL_FIRST);

//Clean all allocated problem
	void Clean();

//Try() to solve this problem sequentially.
	bool Try();

//Decompose is called if "this" can not be sequentially solved. It will add new sub-problems to the list
	bool Decompose(CListDTreeNodePtr &decompose);

//Solve is only called at the root of the tree....
	virtual void Solve();

//Wait for the completion of the problem solving
	virtual bool WaitFinish();

//Add a child node
	void AddChild(DTreeNode *p, bool autodelete=false);

//Get/Set bAutoDelete to allow the parent to delete this node automatically or not

	void SetAutoDelete(bool val);
	bool GetAutoDelete();


//contruct the DDG: this problem depends on problem "p"
//constraints: the two problems have the same parent
	void DependOn(DTreeNode *p);

//Return the number of MFLops of the required resource
	virtual real GetFlops();


	bool SetCoeff(real mycoeff);
	real GetCoeff(); // Parallel coefficient

	CListDTreeNodePtr & GetDependency();

	void SetParent(DTreeNode *p);
	DTreeNode * GetParent();


//This 6 methods are for the construction of Sequential diagram only...
	void SetStartStep(int start);
	int  GetStartStep();
	void SetEndStep(int end);
	int GetEndStep();
	void SetTotalStep(int nstep);
	int GetTotalStep();

	virtual bool CreateNextDependency(ProbObj *next); //Internal use
	bool UpdateChildDependency(); //Internal use
	bool UpdateProbNext(ProbObj *p); //Internal use
	bool UpdateProbDependency(DTreeNode *prev); //internal use
	bool InitProbDependency(); //the user should not call this method. Internal use only!

protected:
//This method is used to create the problem and initilize necessary input and output
// The user should overide this method by should not invoke it directly...
	virtual ProbObj *InitProblem(real required_mflops);

	bool ConstructSeqDiagram();
	bool ComputeTimeConstraints();

	DTreeNode *parent;

	real totalflop; // total number of Flop required.
	real timeconstraint; //seconds that the problem should be solved
	real coeff;

	CListDTreeNodePtr decomposition;
	bool bAutoDelete; // Allow the parent to delete this node automatically on parent's destruction

	CListDTreeNodePtr ddg; // list of nodes that this node depends on: a part of DDG of THIS problem, NOT child!

	int startstep, endstep; // information of sequential diagram...
	int totalstep;

//Input and output data for this problem
	ProbObj *sequential;

};





