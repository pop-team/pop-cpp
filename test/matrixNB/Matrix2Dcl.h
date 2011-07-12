#ifndef _MATRIX2DCL_H
#define _MATRIX2DCL_H
#include "Matrix2D.h"

class Matrix2Dcl : virtual public Matrix2D
{
public:
	Matrix2Dcl();
	Matrix2Dcl(int line, int col);

	void display();
	void display(int n);

	ValueType get(int line, int col);
	void  set(int line, int col, ValueType v);

	Matrix2Dcl getColsBloc(int noCol, int nbCols);
	void setColsBloc(int noCol, Matrix2Dcl v);
	void setBloc(int noLine, int noCol, Matrix2Dcl v);
};
#endif
