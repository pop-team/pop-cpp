#include <iostream>
#include "xmpworker.ph"
#include <unistd.h>


void print_line(double* c) 
{
  for (int i = 0; i < 12; i++) {
    printf("%8.2f  ", c[i]); 
  }
  printf("\n"); 
}


int main(int argc, char* argv[]) {
  std::cout << "Matrix multiplication with POP-C++/XMP" << std::endl; 


  XMPWorker xmp; 
  xmp.initialize(4); 
  xmp.init_xmp(); 

  xmp.compute(); 

  double c[12][12]; 
  int index = 0; 
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      xmp[i].get_row_c(j, 12, c[index]); 
      index++; 
    }
  }

  sleep(1);   


  std::cout << "===== RESULT ======" << std::endl; 
  for(int i = 0; i < 12; i++) {
    for(int j = 0; j < 12; j++) {
      printf("%8.2f  ", c[j][i]); 
    }
    printf("\n"); 
  }
  xmp.finalize(); 
  std::cout << "Matrix multiplication with POP-C++/XMP. TERMINATED SUCCESSFULLY!" << std::endl; 
  return 0; 
}
