#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "modelgene.h"

int compareIndv(CRealArray **v1, CRealArray **v2)
{
	assert((*v1)!=NULL && (*v2)!=NULL && (*v1)->GetSize()==(*v2)->GetSize());
	int n=(*v1)->GetSize()-1;
	if ((**v1)[n]<(**v2)[n]) return -1;
	if ((**v1)[n]>(**v2)[n]) return 1;
	return 0;
}

ModelGenetic::ModelGenetic(int pop, int cross_rate, int mutation_rate)
{
	crossoverrate=cross_rate;
	mutationrate=mutation_rate;

	Nt=Ns=0;
	actualsize=Np=pop;
	keepbests=Np/2;
	if (keepbests<=0) keepbests=1;

	population.SetSize(4*Np);
	for (int i=0;i<4*Np;i++)
	{
		population[i]=new CRealArray();
		assert(population[i]!=NULL);
	}
}

ModelGenetic::~ModelGenetic()
{
	for (int i=0;i<population.GetSize();i++) if (population[i]!=NULL) delete population[i];
}

bool ModelGenetic::Init(int NStep, int NTask, real *Complexities, int *fromstep, int *tostep)
{
	Nt=NTask;
	Ns=NStep;

	complexities.SetSize(Nt);
	startStep.SetSize(Nt);
	endStep.SetSize(Nt);
	for (int i=0;i<Nt;i++)
	{
		complexities[i]=Complexities[i];
		startStep[i]=fromstep[i];
		endStep[i]=tostep[i];
	}

	//Initialize the population....
	int n=population.GetSize();

	paroc_array<int> tmp;
	tmp.SetSize(Ns);
	for (int i=0;i<n;i++)
	{
		CRealArray &indv=(*population[i]);
		indv.SetSize(Ns+1);
		if (i>=Np) continue;
		int total=0;
		for (int j=0;j<Ns;j++)
		{
			total+=(tmp[j]=rand()%10000+1);
		}
		for (int j=0;j<Ns;j++) indv[j]=(tmp[j]*1.0)/total;
	}
	return true;
}

void ModelGenetic::Normalize()
{
	for (int i=0;i<Np;i++)
	{
		real total=0;
		CRealArray &indv=(*population[i]);
		for (int j=0;j<Ns;j++) total+=indv[j];
		assert(total>0);
		for (int j=0;j<Ns;j++) indv[j]/=total;
		EvalFitness(indv);
	}
}

int ModelGenetic::Solve(int maxepoch)
{
	if (Ns<=1)
	{
		(*population[0])[0]=1;
		EvalFitness(*(population[0]));
		return 0;
	}
	real best;
	for (int i=0;i<Np;i++) EvalFitness(*(population[i]));
	qsort((CRealArray **)population,Np,sizeof(CRealArray *),( int (*)(const void *, const void *))compareIndv);
	best=(*population[0])[Ns];

	int lastbest=0;
	for (int i=0;i<maxepoch;i++)
	{
		if (i%100==0) Normalize();

		actualsize=Np;
		for (int j=0;j<Np;j++)
		{
			if (!CrossOver(j)) Mutation(j);
		}
		qsort((CRealArray **)population,actualsize,sizeof(CRealArray *),( int (*)(const void *, const void *))compareIndv);
		if (best> (*population[0])[Ns])
		{
			best=(*population[0])[Ns];
			lastbest=i;
//	  fprintf(stderr,"Best of #%d: %g\n",i,best);
		} else if (i-lastbest>200) return i;
	}
	return maxepoch;
}

real ModelGenetic::GetResults(CRealArray &ret)
{
	ret.SetSize(Ns);
	for (int i=0;i<Ns;i++) ret[i]=(*population[0])[i];
	return (*population[0])[Ns];
}

void  ModelGenetic::ListTaskPower()
{
	CRealArray &steps=(*population[0]);
	for (int i=0;i<Nt;i++)
	{
		real t=0;
		int s=startStep[i];
		int e=endStep[i];
		for (int j=s;j<=e;j++) t+=steps[j];
		printf("TASK #%d: %g\n",i,double(complexities[i]/t));
	}
}

bool ModelGenetic::CrossOver(int indv)
{
	if (rand()%101 > crossoverrate) return false;
	assert(indv>=0 && indv<Np);
	int indv2=rand()%Np;
	if (indv==indv2) return false;
	int pos=rand()%Ns;
	int pos1=pos+1+rand()%(Ns-1);

	static CRealArray new1, new2;
	new1.SetSize(Ns+1);
	new2.SetSize(Ns+1);
	real total1=0,total2=0;
	int endpos=pos+Ns-1;
	real v1,v2;

	real *new1ptr=new1+pos;
	real *new2ptr=new2+pos;
	real *indvptr=(*(population[indv]))+pos;
	real *indv2ptr=(*(population[indv2]))+pos;

//tmp*: for debug...
//  real tmp1=0;
//  real tmp2=0;

	for (int i=pos;i<=endpos;i++, new1ptr++, new2ptr++, indvptr++, indv2ptr++)
	{
		if (i==Ns)
		{
			new1ptr=new1;
			new2ptr=new2;
			indvptr=(*(population[indv]));
			indv2ptr=(*(population[indv2]));
		}
		if (i<pos1)
		{
			total1+=(*new1ptr=*indv2ptr);
			total2+=(*new2ptr=*indvptr);
		}
		else
		{
			if (i==pos1)
			{
				v1=1-(total1-total2)/(1-total2);
				v2=1-(total2-total1)/(1-total1);
//		tmp1=total1;
//		tmp2=total2;
			}
			*new1ptr=(*indvptr)*v1;
			*new2ptr=(*indv2ptr)*v2;

//	    tmp1+=*new1ptr;
//	    tmp2+=*new2ptr;
		}
	}

//    if (fabs(tmp1-1)>0.01 || fabs(tmp2-1)>0.01)
//    {
//        printf("Total New crossover(%d: %g <-> %d: %g) (pos=%d, pos1=%d)\n",indv,tmp1,indv2,tmp2,pos,pos1);
//        tmp1=tmp2=0;
//        for (int i=0;i<Ns;i++)
//        {
//  	  tmp1+=(*population[indv])[i];
//  	  tmp2+=(*population[indv2])[i];
//        }
//        printf("\tCrossover violated the constraints: total before: %d: %g <-> %d: %g\n",indv,tmp1,indv2,tmp2);
//    }

	EvalFitness(new1);
	EvalFitness(new2);
	if (indv>= keepbests)
	{
		(*population[indv])=new1;
	} else
	{
		(*population[actualsize])=new1;
		actualsize++;
	}
	if (indv2>=keepbests)
	{
		(*population[indv2])=new2;
	} else
	{
		(*population[actualsize])=new2;
		actualsize++;
	}
	return true;
}

bool ModelGenetic::Mutation(int indv)
{
	if (rand()%101 > mutationrate) return false;
	assert(indv>=0 && indv<Np);


	static CRealArray new1;
	new1.SetSize(Ns+1);

	real * indvptr=(*population[indv]);
	real *new1ptr=new1;

	if (rand()%10<6)
	{
		int pos=rand()%Ns;
		real delta=0.5*((rand()%2)*2-1)*(rand()%100000+1)/100000.0;
		real *indvpos=indvptr+pos;
		real *newpos=new1ptr+pos;

		real total=1+delta*(*indvpos);

		for (int i=0;i<Ns;i++, indvptr++, new1ptr++)
		{
			*new1ptr=(*indvptr)/total;
		}
		*newpos=(delta+1)*(*indvpos)/total;
	}
	else
	{
		int pos=rand()%Ns;
		int pos1=pos+rand()%(Ns-1);
		int endpos=pos+Ns-1;
		real *indvpos=indvptr+pos;

		int j=pos+1;
		for (int i=pos;i<=endpos;i++,new1ptr++)
		{
			*new1ptr=*indvpos;
			if (i<=pos1)
			{
				if (i==pos1)
				{
					indvpos=indvptr+ ( pos ? (pos-1) : (Ns-1) );
				}
				else if (i==Ns-1) indvpos=indvptr;
				else indvpos++;
			} else
			{
				if (indvpos==indvptr) indvpos=indvptr+Ns-1;
				else indvpos--;
			}
		}
	}
	EvalFitness(new1);

	//DEBUG..
//    real tmp=0;
//    for (int i=0;i<Ns;i++) tmp+=new1[i];
//    if (fabs(tmp-1)>0.01)
//    {
//        printf("Mutation on indv %d violated the constraints (%g)\n",indv,tmp);
//        assert(0);
//    }

	if (indv>= keepbests)
	{
		(*population[indv])=new1;
	} else
	{
		(*population[actualsize])=new1;
		actualsize++;
	}

	return true;
}


real ModelGenetic::EvalFitness(CRealArray &indv)
{
	assert(indv.GetSize()==Ns+1);
	real v=0;
	int *startptr=startStep;
	int *endptr=endStep;
	real *complexitiesptr=complexities;

	for (int i=0;i<Nt;i++,startptr++,endptr++, complexitiesptr++)
	{

		int &s=(*startptr);
		int &e=(*endptr);
//evaluate complexity for task i from step s to step e....
		if (s>=0 && s<=e && e<Ns)
		{
			real sum=0;
			real t=0;
			real *indvptr=indv+s;
			for (int j=s;j<=e;j++,indvptr++) sum+=*indvptr;
			t=(*complexitiesptr)/sum;
			if (t>v) v=t;
		}
	}
	return (indv[Ns]=v);

}
