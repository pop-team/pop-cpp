#include "matrix.ph"
#include "timer.h"
#include <stdio.h>
int main(int argc, char **argv)
{
  int n,m,m1,p;
  int np;

  printf("Enter sizeof matrix A:\n");
  scanf("%d%d",&n,&m);

  printf("Enter sizeof matrix B:\n");
  scanf("%d%d",&m1,&p);
  if (m1!=m)
    {
      printf("Sizes of matrice didn't match\n");
      return 1;
    }
  printf("Enter number of solver:\n");
  scanf("%d",&np);
  if (np<=0) 
    {
      printf("Number of solvers is not valid\n");
      return 1;
    } 
  Matrix mt(n,m,p);
  printf("Allocated Matrix Object\n");
  mt.InitSolver(np);
  for (int i=0;i<np;i++) 
    {
	char str[256];
	mt.GetResource(i,str);
	printf("Solver #%d on %s\n",i,str);
    }
  mt.Init();
  printf("Initialized data\nPress a \"C\" key...\n");

  while (getchar()!='C');

  printf("Now go to solve...\n");
  Timer timer;
  double inittime,waittime;
  timer.Start();
  mt.Solve(inittime,waittime);
  timer.Stop();
  printf("Matrix::Solve returned...Total time: %g sec (In Solve: init=%g, wait=%g)\n",timer.Elapsed(), inittime,waittime);

  char str[256]="/tmp/matrix.out";
  if (paroc_utils::checkremove(&argc,&argv,"-save")!=NULL) mt.Save(str);
  return 0;
 
  
}










