// Matrix multiplication parallel version Matrix B sent in N shots
// Version without parameter for POP-C++ test suite
// Authors: Pierre Kuonen
// 13.9.2009

#include <stdio.h>
#include <timer.h>
#include "Matrix2Dlc.h"
#include "Matrix2Dcl.h"
#include "MatWorker.ph"

#include <iostream>
#include <fstream>
#include <string>

#define toDisplay 5
#define nbMaxMachines 10
#define MachinesList "machines.ip"

ValueType check(int j, int k, int size,  Matrix2Dlc* a, Matrix2Dcl* b)
{
	ValueType v = 0.0;
	for (int l=0; l<size; l++)
		v=v+(a->get(j,l) * b->get(l,k));
	return v;
}


int main(int argc, char** argv)
{
	if (argc<4)
	{
		printf("Usage: popcrun obj.map %s size nbWorker nbBlocB resultFileName\n\n", argv[0]);
		printf("  e.g. : popcrun obj.map %s 600 10 5 log\n\n", argv[0]);
		return -1;
	}

	int Alines;
	int Acols;
	int Bcols;
	int nbWorker;
	int nbBlocB;

	char* resultFileName; //argv[4];

	FILE *f;
	POPString* machine[nbMaxMachines];
	int nbOfMachines  = 0;

	// Get the execution parameters
	Alines= Acols = Bcols = atoi(argv[1]);
	nbWorker = atoi(argv[2]);
	nbBlocB = atoi(argv[3]);
	if (argc>4) resultFileName=argv[4]; else resultFileName=NULL;

// Get the available machines
	if ( (f = fopen(MachinesList, "r"))!=NULL)
	{
		char* s;
		s=(char*)malloc(100);
		while (fscanf(f, "%s", s)!=EOF)
		{
			machine[nbOfMachines] = new POPString(s);
			nbOfMachines++;
		}
		fclose(f);
	}
	else
	{
		for (nbOfMachines=0; nbOfMachines<nbWorker; nbOfMachines++)
			machine[nbOfMachines] = new POPString("localhost");
		nbOfMachines=nbWorker;
	}

	printf("\nMatrix: Starting test..\n");


	printf("Matrix: Available machines:\n");

	for (int i=0; i<nbOfMachines; i++)
		printf("Matrix  %d = %s \n", i, (const char*)(*machine[i]));

	if ((Alines % nbWorker) != 0)
	{
		printf("Size of the Matrix must a muliple of nb. workers\n\n");
		return -1;
	}
	if ((Alines % nbBlocB) != 0)
	{
		printf("Size of the Matrix must a muliple of nb. bloc of B\n\n");
		return -1;
	}

	printf("\nMatrix size = %d  Nb. Workers = %d  Nb. Blocs = %d \n\n", Alines, nbWorker, nbBlocB);

	// Matrix A and B declaration and initialisation
	Matrix2Dlc a(Alines,Acols);
	Matrix2Dcl b(Acols,Bcols);

	a.init();
	printf("Matrix A:%dx%d\n",a.getLines(),a.getCols());
	a.display(toDisplay);printf("\n");

	b.init();
	printf("Matrix: B:%dx%d\n",b.getLines(),b.getCols());
	b.display(toDisplay);printf("\n");



	//Workers declaration

	MatWorker* mw[nbWorker];
	Timer timer;

	double initTime, totalTime, sendTime;

	timer.Start();



	//Workers creation

	srand(time(NULL));

	int shift = rand() % nbOfMachines;

	printf("\n");

	try
	{
		for (int i=0; i<nbWorker; i++)
		{
			mw[i] = new MatWorker(i, Alines/nbWorker, Acols, Bcols, *(machine[(i+shift)%nbOfMachines]));
		}

		printf("\nMatrix: Start computation...\n");



		// Get the time necessary to create all workers

		initTime = timer.Elapsed();



		//Send the bloc of Matrix A and the 1st bloc of Matrix B

		for (int i=0; i<nbWorker; i++)
			mw[i]->solve(a.getLinesBloc(i*Alines/nbWorker,Alines/nbWorker),
						 b.getColsBloc(0,Bcols/nbBlocB));



		//Send the others blocs of Matrix B
		for (int j=1; j<nbBlocB; j++)
			for (int i=0; i<nbWorker; i++)
				mw[i]->putB(b.getColsBloc(j*Bcols/nbBlocB,Bcols/nbBlocB));



		// Get the time necessary to send all data to workers

		sendTime = timer.Elapsed() - initTime;

		// Check calculation of the (checkI,checkJ) value
		srand(time(NULL));
		int checkI = rand() % Alines;
		int checkJ = rand() % Alines;
		ValueType checkV = check(checkI,checkJ, Alines, &a, &b);


		//Create matrix for getting the results

		Matrix2Dlc res(Alines/nbWorker,Bcols);
		double workerT[nbWorker];

		//Get the result and put inside matrix A
		for (int i=0; i<nbWorker; i++)
		{
			res=mw[i]->getResult(workerT[i]);
			a.setLinesBloc(i*Alines/nbWorker, res);
		}

		// Get the elapsed time since all workers have been created

		totalTime = timer.Elapsed() - initTime;

		timer.Stop();

		printf("Matrix: ...End of computation\n");

		printf("Matrix:  A*B:%dx%d\n",a.getLines(),a.getCols());
		a.display(toDisplay);printf("\n");
		printf("Matrix: Time (init, send and wall) = %g %g %g sec\n\n",initTime, sendTime, totalTime);

		if ((int)checkV==(int)a.get(checkI,checkJ))
			printf("Matrix: test succeeded (%d,%d), destroying objects...\n",checkI,checkJ);
		else
			printf("Matrix: Test failed (%d,%d), NON-Correct calculation !!\n",checkI,checkJ);


		// Delete the workers

		for (int i=0; i<nbWorker; i++) if (mw[i]!=NULL) delete mw[i];

	} // end try



	catch (POPException *e)

	{

		printf("Matrix: Test failed, Object creation failure\n");

		return 0;

	}

	return 0;

}

