#include "MatWorker.ph"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

MatWorker::MatWorker()
{
	nbLinesA = 0;
	nbColsA = 0;
	nbColsB = 0;
	id = 0;
	resMatrix = NULL;
	bMatrix = NULL;

	sizeB=0;
	nextBbloc=false;
}

MatWorker::MatWorker(int i, int nbLineA, int nbColA, int nbColB, POPString machine)
{
	nbLinesA = nbLineA;
	nbColsA = nbColA;
	nbColsB = nbColB;
	id = i;
	resMatrix = new Matrix2Dlc(nbLineA,nbColB);
	resMatrix->zero();

	sizeB=0;
	nextBbloc=false;
	printf("Worker %d created on machine:%s\n",i, (const char*)POPSystem::GetHost());
}

MatWorker::~MatWorker()
{
	if (resMatrix != NULL) delete resMatrix;
	if (bMatrix != NULL) delete bMatrix;
}

void MatWorker::solve(Matrix2Dlc a, Matrix2Dcl b)
{
	timer.Start();
	bMatrix = new Matrix2Dcl(b.getLines(),b.getCols());
	bMatrix->setColsBloc(0,b);
	do {
		x.lock();
		if (nextBbloc) x.wait();
		for (int j=0; j<nbLinesA; j++)
			for (int k=0; k<b.getCols(); k++)
				for (int l=0; l<nbColsA; l++)
					resMatrix->set(j,k+sizeB,
								   resMatrix->get(j,k+sizeB)+a.get(j,l)*bMatrix->get(l,k));
		sizeB = sizeB + b.getCols();
		nextBbloc=true;
		x.raise();
		x.unlock();
	} while (sizeB<nbColsB);
	computeTime=timer.Elapsed(); timer.Stop();
}

void MatWorker::putB(Matrix2Dcl b)
{
	x.lock();
	if (!nextBbloc) x.wait();
	bMatrix->setColsBloc(0,b);
	nextBbloc=false;
	x.raise();
	x.unlock();
}


Matrix2Dlc MatWorker::getResult(double &t)
{
	t = computeTime;
	return *resMatrix;
}

@pack(MatWorker);
