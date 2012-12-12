/**
 *
 */
 
#include <stdio.h>

#define NUM_ROWS_A 12 //rows of input [A]
#define NUM_COLUMNS_A 12 //columns of input [A]
#define NUM_ROWS_B 12 //rows of input [B]
#define NUM_COLUMNS_B 12 //columns of input [B]

#pragma xmp nodes p(*)
#pragma xmp template t(0:11) 
#pragma xmp distribute t(block) onto p


double a[NUM_ROWS_A][NUM_COLUMNS_A]; //declare input [A]
double b[NUM_ROWS_B][NUM_COLUMNS_B];
double c[NUM_ROWS_A][NUM_COLUMNS_B]; 

#pragma xmp align b[i][*] with t(i)
#pragma xmp align c[i][*] with t(i)


int main(void){
  int i;

#pragma xmp loop on t(j)
  for (int j = 0; j < NUM_COLUMNS_B; j++) {
    for(int i= 0; i < NUM_ROWS_A; i++) {
      for(int k = 0; k < NUM_COLUMNS_A; k++) {
        c[j][i] = c[j][i] + a[k][i] * b[j][k];
        
        printf("Process %d is computing c[%d][%d]\n", xmp_node_num(), j, i); 

      } 
    }
  }

  return 0;
}


 
