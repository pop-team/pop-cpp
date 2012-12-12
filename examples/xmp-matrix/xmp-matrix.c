/**
 *
 */
 
#include <stdio.h>

#define NUM_ROWS_A 12 //rows of input [A]
#define NUM_COLUMNS_A 12 //columns of input [A]
#define NUM_ROWS_B 12 //rows of input [B]
#define NUM_COLUMNS_B 12 //columns of input [B]

#pragma xmp nodes p(*)
double mat_a[NUM_ROWS_A][NUM_COLUMNS_A]; //declare input [A]

#pragma xmp template t(0:12)
#pragma xmp distribute t(block) onto p
#pragma xmp align mat_a[*][i] with t(i)

//double mat_b[NUM_ROWS_B][NUM_COLUMNS_B]; //declare input [B]
//double mat_result[NUM_ROWS_A][NUM_COLUMNS_B]; //declare output [C]

#pragma xmp align mat_a[i] with t(i)

int main(void){
  int i;

#pragma xmp loop on t(i)
  for(i = 0; i < NUM_ROWS_A; i++)
    printf("%d %d\n", xmp_node_num(), mat_a[i][0]);

  return 0;
}


 