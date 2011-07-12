#ifndef _MATRIX2D_H
#define _MATRIX2D_H

#define ValueType float
#define ValueTypeSize sizeof(ValueType)

class Matrix2D : public POPBase   // mxn 2D Matrix with values of type "ValueType"


{
public:
	Matrix2D();
	Matrix2D(int line, int col);
	Matrix2D(const Matrix2D &m);
	~Matrix2D();

	void init();                 // Init Matrix random values
	void init(char* filename);   // Init Matrix from a file
	void fill(ValueType v);      // Fill Matrix with v

	void zero();  // Fill Matrix with 0
	void null();  // Make the Matrix a 0x0 Matrix
	void free();  // Free the memory used  by data but keep size info  (nxm)

	virtual ValueType get(int line, int col);          // get values of line,col
	virtual void  set(int line, int col, ValueType v); // set values of line,col

	int getLines();                   // get value of m
	int getCols();                     // get value of n

	virtual void display();       // Display the Matrix content
	virtual void display(int n);  // Display only partially the Matrix content

	void operator=(Matrix2D m);   // Affectation operator for Matrix 2D

	void showState(const char* s, bool all); // Display information on the Matrix status

	// Serialize Matrix 2D for POP-C++ usage


	void Serialize(POPBuffer &buf, bool pack);

protected:
	int nbLine;    //Nb. lines of the matrix
	int nbCol;     //Nb. columns of the matrix
	int dataSize;  //Current size (in byte) of the attached matrix
	ValueType* shared; //The other data matrix I am using
	ValueType* value;  //The matrix data
};
#endif
