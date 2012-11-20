#ifndef _MATWORKER_PH
#define _MATWORKER_PH

#include <timer.h>
#include "Matrix2Dlc.h"
#include "Matrix2Dcl.h"

parclass MatWorker
{
	classuid(1500);

public:
	MatWorker();
	MatWorker(int i, int nbLineA, int nbColA, int nbColB, int node) @{ od.node(node); od.executable("./MatWorker.obj"); };
	~MatWorker();

	async conc void solve(Matrix2Dlc a, Matrix2Dcl b);
	async seq void putB([in]Matrix2Dcl b);

	sync mutex Matrix2Dlc getResult(double &t);

private:
	Matrix2Dlc* resMatrix;
	Matrix2Dcl* bMatrix;
	int nbLinesA, nbColsA, nbColsB;
	int id;
	POPSynchronizer x;
	bool nextBbloc;

	Timer timer;
	double computeTime;

	int sizeB;
};
#endif
