#include "popgroup.ph"
#include "popc_group_exception.h"

#include <iostream>

int main(int argc, char* argv[]){
  printf("POG Test case started ...\n"); 
  int testnb = 11; 

  int testret[testnb];
  for( int i = 0; i < testnb; i++ ) {
    testret[i] = 1; 
  }
 
  POPGroup group1;
  POPGroup group2; 
  
  // Test not initialized exception on merge
  try {
    group1.merge(group2); 
  } catch (POPC_GroupException* e) {
    testret[0] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }

  // Test not initialized exception on split
  try {
    group1.split(5); 
  } catch (POPC_GroupException* e) {
    testret[1] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  // Test not initialized exception on split
  try {
    int g1[2] = { 1, 3 }; 
    int g2[2] = { 0, 2 }; 
    group1.split(g1, 2, g2, 2); 
  } catch (POPC_GroupException* e) {
    testret[2] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }

  // Test not initialized exception on remove
  try {
    group1.remove(5); 
  } catch (POPC_GroupException* e) {
    testret[3] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }

  group1.initialize(2); 
  
  // Test not initialized exception on merge with one initialized group
  try {
    group1.merge(group2); 
  } catch (POPC_GroupException* e) {
    testret[4] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }

  group2.initialize(2); 
  
  // Test not implemented exception on merge with two initialized group
  try {
    group1.merge(group2); 
  } catch (POPC_GroupException* e) {
    testret[5] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  
  // Test not implemented exception on split
  try {
    group1.split(1); 
  } catch (POPC_GroupException* e) {
    testret[6] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  // Test not implemented exception on split
  try {
    int g1[1] = { 0 }; 
    int g2[1] = { 1 }; 
    group1.split(g1, 1, g2, 1); 
  } catch (POPC_GroupException* e) {
    testret[7] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  // Test not implemented exception on remove
  try {
    group1.remove(1); 
  } catch (POPC_GroupException* e) {
    testret[8] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  
  // Test out of group exception on remove
  try {
    group1.remove(10); 
  } catch (POPC_GroupException* e) {
    testret[9] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  // Test out of group exception on split 1
  try {
    group1.split(10); 
  } catch (POPC_GroupException* e) {
    testret[10] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }
  
  // Test out of group exception on split 2
  try {
    int g1[1] = { 10 }; 
    int g2[1] = { 11 }; 
    group1.split(g1, 1, g2, 1); 
  } catch (POPC_GroupException* e) {
    testret[10] = 0; 
    std::cout << "Exception occurred: " << e->what() << std::endl;
  }

  for(int i = 0; i < testnb; i++) {
    if(testret[i] != 0) {
      printf("POG test case failed %d ...\n", i); 
      return 1; 
    }
  }

  printf("POG test case succeed ...\n"); 
  return 0; 
}
