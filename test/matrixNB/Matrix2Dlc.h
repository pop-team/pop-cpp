#ifndef _MATRIX2DLC_H
#define _MATRIX2DLC_H
#include "Matrix2D.h"

class Matrix2Dlc : virtual public Matrix2D
{
public:
	Matrix2Dlc();
	Matrix2Dlc(int line, int col);

	ValueType get(int line, int col);
	void  set(int line, int col, ValueType v);

	void display();
	void display(int n);

	Matrix2Dlc getLinesBloc(int noLine, int nbLines);
	void setLinesBloc(int noLine, Matrix2Dlc v);
	void setBloc(int noLine, int noCol, Matrix2Dlc v);
};
#endif
