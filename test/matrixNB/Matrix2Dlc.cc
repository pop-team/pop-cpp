#include <stdlib.h>
#include <stdio.h>
#include "Matrix2Dlc.h"

Matrix2Dlc::Matrix2Dlc()
{
}

Matrix2Dlc::Matrix2Dlc(int line, int col): Matrix2D(line,col)
{
}

inline ValueType Matrix2Dlc::get(int line, int col)
{
	return value[line*nbCol+col];
}

inline void Matrix2Dlc::set(int line, int col, ValueType v)
{
	value[line*nbCol+col]=v;
}

Matrix2Dlc Matrix2Dlc::getLinesBloc(int noLine, int nbLines)
{
	if ( (value!=NULL) || (nbLine>=(noLine+nbLines)) )
	{
		Matrix2Dlc tmp;
		tmp.nbCol = nbCol;
		tmp.nbLine = nbLines;
		tmp.dataSize = dataSize;
		tmp.value = &(value[noLine*nbCol]);
		if (shared==NULL) tmp.shared = value; else tmp.shared=shared;
		if (tmp.shared!=NULL) (tmp.shared[dataSize])= (tmp.shared[dataSize])+(ValueType)1;
		//tmp.showState("Getting lines DONE:", true);
		return tmp;
	}
	else
	{
		Matrix2Dlc tmp;
		showState("ERROR Getting lines:", false);
		return tmp;
	}
}

void Matrix2Dlc::setBloc(int noLine, int noCol, Matrix2Dlc v)
{
	if ((nbCol>=noCol+v.nbCol) && (nbLine>=(noLine+v.nbLine)) )
	{
		if (value==NULL)
		{
			dataSize = nbLine*nbCol;
			value = (ValueType*)malloc((dataSize+1)*ValueTypeSize);
			if (value==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
			value[dataSize]=0;
			shared = NULL;
		}
		for (int i=0; i<v.nbLine; i++)
			memcpy(&(value[(noLine+i)*nbCol+noCol]),&(v.value[i*v.nbCol]), v.nbCol*sizeof(ValueType));
		// memcpy replaces the following for loop
		//for (int j=0; j<v.nbCol; j++)
		//value[(noLine+i)*nbCol+noCol+j]=v.value[i*v.nbCol+j];
	}
	else printf("Matrix ERROR: Non coherent bloc setting !!!\n");
}

void Matrix2Dlc::setLinesBloc(int noLine, Matrix2Dlc v)
{
	if ((nbCol==v.nbCol) && (nbLine>=(noLine+v.nbLine)) )
	{
		if (value==NULL)
		{
			dataSize = nbLine*nbCol;
			value = (ValueType*)malloc((dataSize+1)*ValueTypeSize);
			if (value==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
			value[dataSize]=0;
			shared = NULL;
		}
		memcpy(&(value[noLine*nbCol]), v.value, v.nbCol*v.nbLine*sizeof(ValueType));
		// memcpy replaces the following for loop
		//for (int i=0; i<v.nbCol*v.nbLine; i++)
		//value[noLine*nbCol+i]=v.value[i];
	}
	else printf("Matrix ERROR: Non coherent line setting !!!\n");
}

void Matrix2Dlc::display()
{
	if (value!=NULL)
		for (int i=0; i<nbLine; i++)
		{
			for (int j=0; j<nbCol; j++)
				printf("%8.1lf ",(double)value[i*nbCol+j]);
			printf("\n");
		}
	printf("....................\n");
}

void Matrix2Dlc::display(int n)
{
	if (n>nbLine) n=nbLine; if (n>nbCol) n=nbCol;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			printf("%6.1f ",(float)value[i*nbCol+j]);
		printf("..\n");
	}
	printf("....................\n");
}

