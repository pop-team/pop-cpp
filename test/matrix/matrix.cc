#include <stdio.h>
#include "matrix.ph"
#include <stdlib.h>
#include <errno.h>

MatrixMul::MatrixMul()
{
    B=NULL;
    results=buf[1]=buf[0]=NULL;
    id=0;
    bufid=0;
    nrow=20;
}

void MatrixMul::SetId(int anid)
{
  id=anid;
}
void MatrixMul::Solve(int m, int p,  Matrix & data)
{
    if (B!=NULL) delete B;
    B=new float[m*p];
    if (B==0) throw errno;
    data.GetBData(B,m*p);
    Solve(m,p,B,data);
}

void MatrixMul::Solve(int m, int p,float *B, Matrix & data)
{
  //  printf("In MatrixMul::Solve(#%d)...%dx%d X %dx%d, startrow=%d [%g,...,%g]\n",id,n,m,m,p,Astartrow,B[0],B[m*p-1]);
  if (m<=0 || p<=0) return;

  if (results!=NULL) delete results;
  if (buf[0]!=NULL) delete buf[0];
  if (buf[1]!=NULL) delete buf[1];
  results=new float[nrow*p];
  if (results==NULL) throw errno;
  buf[0]=new float[m*nrow];
  buf[1]=new float[m*nrow];

  bufid=0;
  data.NeedData(id,nrow,0,0,NULL,0);
  int firsttime=true;

  while (1)
  {
      int event=eventwait(ANY_EVENT);
      if (event!=0 && event!=1) break;
      bufid=!bufid;
      int howmany=howmanyrow[event];
      if (howmany)
      {
	  if (firsttime)
	  {
	      data.NeedData(id,nrow,0,0,NULL,0);
	      firsttime=false;
	  } else data.NeedData(id,nrow,rowindex[!event],howmanyrow[!event],results,p*howmanyrow[!event]);  
      } else
      {
	  if (!firsttime)  data.NeedData(id,0,rowindex[!event],howmanyrow[!event],results,p*howmanyrow[!event]);
	  break;
      }

      float *mybuf=buf[event];
      float *current=results;
      register float tmpsum;

      for (int i=0;i<howmany; i++, mybuf+=m)
      {
	  for (int j=0;j<p;j++, current++)
	  {
	      tmpsum=0;
	      float *tmp=mybuf;
	      float *Bcol=B+j;
	      for (int k=0;k<m;k++, Bcol+=p, tmp++)
	      {
		  tmpsum+=(*Bcol)*(*tmp);
	      }
	      *current=tmpsum;
	  }
      }
  }
  //  printf("MatrixMul::Solve anded\n");
}

void MatrixMul::SetData(int row,  int howmany, float *dat, int sz)
{
    if (sz>0)
    {
	if (howmany>nrow) howmany=nrow;
	memcpy(buf[bufid],dat,sz*sizeof(float));
	rowindex[bufid]=row;
	howmanyrow[bufid]=howmany;
    } else howmanyrow[bufid]=0;
    eventraise(bufid);
}

MatrixMul::~MatrixMul()
{
  if (results!=0) delete results;
  if (buf[0]!=NULL) delete buf[0];
  if (buf[1]!=NULL) delete buf[1];
  if (B!=NULL) delete B;
}

void MatrixMul::GetResource(char *myresource)
{
	strcpy(myresource,(const char *)paroc_system::GetHost());
}

//Matrix data class
Matrix::Matrix(int n, int m, int p)
{
  Arows=n;
  Acols=m;
  Bcols=p;
  results=new float[n*p];
  if (results==NULL) throw errno;
  A=new float[n*m];
  if (A==NULL) throw errno;
  B=new float[m*p];
  if (B==NULL) throw errno;
  np=0;
  currentrow=0;
  memset(engines,0,MAXNP*sizeof(MatrixMul *));
}

Matrix::~Matrix()
{
  DEBUG("Now destroy matrix object (%d solvers)\n",np);	
  for (int i=0;i<np;i++) if (engines[i]!=NULL) delete (engines[i]);

  if (A!=NULL) delete A;
  if (B!=NULL) delete B;
  if (results!=NULL) delete results;
 
  
}

void Matrix::InitSolver(int nsolver)
{
  if (nsolver>MAXNP) nsolver=MAXNP;
  for (int i=0;i<np;i++) if (engines[i]!=NULL) 
  {
     delete engines[i];
     engines[i]=NULL;
  }		
  np=nsolver;

  DEBUG("Number of Solver to be allocated: %d\n",np);
  for (int i=0;i<nsolver;i++)
  {
      engines[i]=new MatrixMul;
      engines[i]->SetId(i);
  }
}

void Matrix::Init()
{
  float *tmp=A;
  int n=Arows*Acols;
  for (int i=0;i<n;i++) A[i]=rand()%20;
  n=Acols*Bcols;
  for (int i=0;i<n;i++) B[i]=rand()%20;
}

void Matrix::NeedData(int id, int howmany, int startrow, int nrows, float *result, int sz)
{
  //  printf("In Matrix::NeedData: Obj #%d requires data for row %d\n",id,row);
  if (id<0 || id>=np) return;
//Send next request to solver
  mutex {
      if (howmany>0)
      {
	  if (currentrow+howmany>Arows) howmany=Arows-currentrow;
	  if (engines[id]==NULL) return;
	  engines[id]->SetData(currentrow,howmany,A+currentrow*Acols,Acols*howmany);
	  currentrow+=howmany;
      }
  }
//Store the result
  if (sz>0 && startrow>=0 && startrow<Arows && nrows>0)
  {
      if (startrow+nrows>Arows) nrows=Arows-startrow;
      if (sz>nrows*Bcols) sz=nrows*Bcols;

      if (nrows>0)
      {
	  memcpy(results+startrow*Bcols,result,sz*sizeof(float));
      }
      if (startrow+nrows>=Arows) eventraise(1);
  }
}

void Matrix::Solve(double &inittime, double &waittime)
{
  //  printf("In Matrix::Solve..\n");
  if (np<=0) throw OBJECT_NO_RESOURCE;
  currentrow=0;

  Matrix inf(GetAccessPoint());

  timer.Start();  
  for (int i=0;i<np;i++)
    {
      engines[i]->Solve(Acols,Bcols,B, inf);
    }
  inittime=timer.Elapsed();
  timer.Reset();
  eventwait(1);
  waittime=timer.Elapsed();
}


int Matrix::Save(char *fname)
{
  FILE *f=fopen(fname,"w+t");
  if (f==NULL) return errno;
  fprintf(f,"A=%d x %d , B=%d x %d\n",Arows,Acols,Acols,Bcols);
  int n=Arows*Acols;
  fprintf(f,"\nA DATA:");
  for (int i=0;i<n;i++)
    {
      if (i%Acols==0) fprintf(f,"\n");
      fprintf(f,"%g ",A[i]);
    }

  n=Acols*Bcols;
  fprintf(f,"\nB DATA:");
  for (int i=0;i<n;i++)
    {
      if (i%Bcols==0) fprintf(f,"\n");
      fprintf(f,"%g ",B[i]);
    }

  n=Arows*Bcols;
  fprintf(f,"\nA.B DATA:");
  for (int i=0;i<n;i++)
    {
      if (i%Bcols==0) fprintf(f,"\n");
      fprintf(f,"%g ",results[i]);
    }
  return 0;
  
}

void Matrix::GetBData(float *data, int sz)
{
    memcpy(data,B,sz*sizeof(float));
}

void Matrix::GetResource(int id, char *solver)
{
	if (id==-1) strcpy(solver,(const char *)paroc_system::GetHost());
	else if (id>=0 && id<np && engines[id]!=NULL) engines[id]->GetResource(solver);
	else sprintf(solver,"NULL resource %d\n",id);
}













