//A.B [in, size=m*p]
#include "timer.h"
parclass Matrix;

#define MAXNP 100

parclass MatrixMul
{
public:
	MatrixMul() @{ power= 500 ?: 50;};
	sync void SetId(int anid);
	conc  async  void Solve( int m, int p, [in, size=m*p] float *B, [in] Matrix & data);
	conc  async  void Solve( int m, int p, [in] Matrix & data);
	async void SetData(int row, int howmany, [in,size=sz] float *dat, int sz);
	void GetResource([out,size=256] char *myresource);
	~MatrixMul();

	classuid(1500);	
protected:
	int id;

	float *B;
	float *results;

	float *buf[2];
	int rowindex[2];
	int howmanyrow[2];

	int bufid;
	int nrow;
};

parclass Matrix
{
public:
	Matrix(int n, int m, int p) @{ power=500 ?: 50; };
	~Matrix();
	sync void InitSolver(int nsolver);
	mutex sync void Init();
	conc async void NeedData(int id, int howmany, int startrow,
	int nrows, [in, size=sz] float *result, int sz);
	sync  conc void Solve([out] double &inittime,[out] double &waittime);
	sync int Save([in, size=256] char *fname);
	void GetResource(int id, [out,size=256] char *solver);

	conc void GetBData([out,size=sz] float *data, int sz);
	
	classuid(1000);

protected:
	MatrixMul *engines[MAXNP];	
	int np;

	float *A;
	float *B;	
	int Arows, Acols;
	int Bcols;
	float *results;	
	
	int currentrow;
	Timer timer;
};












