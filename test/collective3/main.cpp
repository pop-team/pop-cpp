#include "popobject.ph"

/**
 * 
 * POP-C++ Test Suite: Creation of Parallel Object Group from a parallel object
 * 
 */


int main(int argc, char* argv[]){
  printf("POG Test case started ...\n"); 
  POPObject o1; 
  o1.create_group();
  printf("POG test case finished ...\n"); 
  return 0; 
}
