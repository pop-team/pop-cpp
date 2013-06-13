#include <stdio.h>
#include "test.h"

#pragma xmp nodes p(*)
#pragma xmp template t(0:9)
#pragma xmp distribute t(block) onto p
int a[10];
#pragma xmp align a[i] with t(i)


/*int main(void){
  xmp_function();
  return 0;
}*/

void xmp_function(){
  int i;

#pragma xmp loop on t(i)
  for(i=0;i<10;i++)
    a[i] = i;

#pragma xmp loop on t(i)
  for(i=0;i<10;i++)
    printf("%d %d\n", xmp_node_num(), a[i]);
}
