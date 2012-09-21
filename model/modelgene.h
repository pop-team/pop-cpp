#include "paroc_array.h"
typedef float  real;
typedef paroc_array<real> CRealArray;
typedef paroc_array<CRealArray *> CPtrArrayArray;
typedef paroc_array<int> 	CIntArray;

class ModelGenetic
{
public:
	ModelGenetic(int pop, int cross_rate, int mutation_rate);
	~ModelGenetic();
	bool Init(int NStep, int NTask, real *Complexities, int *fromstep, int *tostep);
	void Normalize();
	int Solve(int maxepoch);
	real GetResults(CRealArray &ret);

	void ListTaskPower();

	bool CrossOver(int indv);
	bool Mutation(int indv);
protected:
	real EvalFitness(CRealArray &indv);

	CPtrArrayArray population;
	int actualsize;
	int keepbests;

	CRealArray complexities;
	paroc_array<int> startStep, endStep;

	int Np; //population size
	int Nt;  //Number of tasks
	int Ns; //Number of steps
	int crossoverrate;
	int mutationrate;
};

