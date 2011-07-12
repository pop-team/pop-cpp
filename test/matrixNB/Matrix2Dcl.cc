#include <stdlib.h>
#include <stdio.h>
#include "Matrix2Dcl.h"

Matrix2Dcl::Matrix2Dcl()
{
}

Matrix2Dcl::Matrix2Dcl(int line, int col) : Matrix2D(line,col)
{
}

inline ValueType Matrix2Dcl::get(int line, int col)
{
	return value[col*nbLine+line];
}

inline void  Matrix2Dcl::set(int line, int col, ValueType v)
{
	value[col*nbLine+line]=v;
}

Matrix2Dcl Matrix2Dcl::getColsBloc(int noCol, int nbCols)
{
	if ((value!=NULL) || (nbCol>=(noCol+nbCols)))
	{
		Matrix2Dcl tmp;
		tmp.nbCol = nbCols;
		tmp.nbLine = nbLine;
		tmp.dataSize = dataSize;
		tmp.value=&(value[noCol*nbLine]);
		if (shared==NULL) tmp.shared = value; else tmp.shared=shared;
		if (tmp.shared!=NULL) (tmp.shared[dataSize])=(tmp.shared[dataSize])+(ValueType)1;
		//tmp.showState("Getting col DONE:", false);printf("\n");
		return tmp;
	}
	else
	{
		Matrix2Dcl tmp;
		showState("ERROR Getting columns:", false);
		return tmp;
	}
}
void Matrix2Dcl::setBloc(int noLine, int noCol, Matrix2Dcl v)
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
		for (int i=0; i<v.nbCol; i++)
			memcpy(&(value[(noCol+i)*nbLine+noLine]),&(v.value[i*v.nbLine]), v.nbLine*sizeof(ValueType));
		// memcpy replaces the following for loop
		//for (int j=0; j<v.nbLine; j++)
		//value[(noCol+i)*nbLine+noLine+j]=v.value[i*v.nbLine+j];
	}
	else printf("Matrix ERROR: Non coherent bloc setting !!!\n");
}

void Matrix2Dcl::setColsBloc(int noCol, Matrix2Dcl v)
{
	if ((nbLine==v.nbLine) && (nbCol>=(noCol+v.nbCol)) )
	{
		if (value==NULL)
		{
			dataSize = nbLine*nbCol;
			value = (ValueType*)malloc((dataSize+1)*ValueTypeSize);
			if (value==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
			value[dataSize]=0;
			shared = NULL;
		}
		memcpy (&(value[noCol*nbLine]),v.value, v.nbCol*v.nbLine*sizeof(ValueType));
		// memcpy replaces the following for loop
		//for (int i=0; i<v.nbCol*v.nbLine; i++)
		//value[noCol*nbLine+i]=v.value[i];
	}
	else printf("Matrix ERROR: Non coherent column setting !!!\n");
}

void Matrix2Dcl::display()
{
	for (int i=0; i<nbLine; i++)
	{
		for (int j=0; j<nbCol; j++)
			printf("%8.1lf ",(double)value[j*nbLine+i]);
		printf("\n");
	}
}

void Matrix2Dcl::display(int n)
{
	if (n>nbLine) n=nbLine; if (n>nbCol) n=nbCol;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
			printf("%6.1f ",(float)value[j*nbLine+i]);
		printf("..\n");
	}
	printf("....................\n");
}
