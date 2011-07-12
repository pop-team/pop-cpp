#include <stdlib.h>
#include <stdio.h>
#include "Matrix2D.h"

Matrix2D::Matrix2D()
{
	nbLine=0; nbCol=0;
	dataSize =0; value = NULL;
	shared=NULL;
	//showState("Created:", false);
}

Matrix2D::Matrix2D(int line, int col)
{
	nbLine=line; nbCol=col;
	dataSize =nbLine*nbCol;
	value=(ValueType*)malloc((dataSize+1)*ValueTypeSize);
	if (value==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
	value[dataSize]=0;
	shared = NULL;
	//showState("Created:", false);
	//printf("Buffer size=%d\n", (int)(&value[nbLine*nbCol])-(int)value);
}

Matrix2D::Matrix2D(const Matrix2D &m)
{
	//showState("\n\nCopying: ", true);
	//printf("\n\nStart Copying: \n", false);
	nbLine = m.nbLine;
	nbCol = m.nbCol;
	dataSize = m.dataSize;
	value = m.value;
	if (m.shared==NULL) shared = value; else shared = m.shared;
	if (shared!=NULL) shared[dataSize] = shared[dataSize] + (ValueType)1;
	//showState("Copying DONE: ", false);
}

Matrix2D::~Matrix2D()
{
	//showState("Destroying:", false);
	free();
	nbLine=0; nbCol=0;
	//showState("Destroy DONE:", false);
}

void Matrix2D::free()
{
	//showState("\n\nFree:", true);
	if (value!=NULL)
	{
		if (shared!=NULL)
		{
			if  (shared[dataSize]<0.9) delete shared;
			else shared[dataSize] = shared[dataSize]-(ValueType)1;
		}
		else
		{
			if (value[dataSize]<0.9) delete value;
			else  value[dataSize] = value[dataSize]-(ValueType)1;
		}
	}
	value=NULL; shared=NULL; dataSize = 0;
	//showState("Free DONE:",false);
}

void Matrix2D::showState(const char* s, bool all)
{
	printf("%s M%dx%d at %p, data size = %d ", s, nbLine, nbCol, value, dataSize);
	if (shared!=NULL) printf("ref=%f, ", shared[dataSize]);
	else if (value!=NULL) printf("ref=%f, ", value[dataSize]);
	printf("shared=%p" , shared);
	if (value!=NULL) printf(" at %p", (&value[dataSize]));
	printf("\n");
	if (all) if (value!=NULL) display();
}

void Matrix2D::init()   //random
{
	srand(time(NULL));
	if (value!=NULL)
		for (int i=0; i<nbCol*nbLine; i++)
			value[i] = ((ValueType)(rand()%200))/7;
}

void Matrix2D::init(char* filename) // from file
{ // Still to write
	if (value!=NULL)
		for (int i=0; i<nbCol*nbLine; i++)
			value[i]=(ValueType)0;
}

void Matrix2D::fill(ValueType v) // fill with v
{
	if (value!=NULL)
		for (int i=0; i<nbCol*nbLine; i++)
			value[i]=(ValueType)v;
}

void Matrix2D::zero() // fill with 0
{
	if (value!=NULL)
		for (int i=0; i<nbCol*nbLine; i++)
			value[i]=(ValueType)0;
}

void Matrix2D::null()  // if possible free memory space used by data
{
	//showState("null:", false);
	free();
	nbLine=0; nbCol=0;
}

inline ValueType Matrix2D::get(int line, int col)
{
	return (ValueType)0;
}

inline void  Matrix2D::set(int line, int col, ValueType v)
{
}

int Matrix2D::getLines() { return nbLine;}
int Matrix2D::getCols() { return nbCol;}


void Matrix2D::operator=(Matrix2D m)
{
	//showState("OPERATOR =", false); /*m.*/showState(" = ", false);
	free();
	nbLine = m.nbLine;
	nbCol = m.nbCol;
	dataSize = m.dataSize;
	value = m.value;
	if (m.shared==NULL) shared = m.value; else shared = m.shared;
	if (shared!=NULL) shared[dataSize] = shared[dataSize] +(ValueType)1;
	//printf("OPERATOR DONE:Mlc%dx%d, value=%d, shared=%d\n", nbLine, nbCol, (int)(value), (int)(shared));
}

void Matrix2D::display()
{
}

void Matrix2D::display(int n)
{
}

void Matrix2D::Serialize(POPBuffer &buf, bool pack)
{
	if (pack)
	{
		int s;
		//showState("\n\nSending ",false);
		buf.Pack(&nbCol,1);
		buf.Pack(&nbLine,1);
		if (value==NULL) s = 0; else s = nbLine*nbCol;
		buf.Pack(&s,1);
		if (s>0) buf.Pack(value, s);
	}
	else
	{
		free();
		buf.UnPack(&nbCol,1);
		buf.UnPack(&nbLine,1);
		buf.UnPack(&dataSize,1);
		shared=NULL;
		if (dataSize>0)
		{
			value=(ValueType*)malloc((dataSize+1)*ValueTypeSize);
			if (value==NULL) {printf("\nMEMORY OVERFLOW !!!!\n"); exit(0);}
			value[dataSize]=0;
			buf.UnPack(value, dataSize);
		}
		else value = NULL;
		//showState("\n\nReceiving ",false);
	}
}

