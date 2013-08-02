/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/12
 * @brief Parallel Object Group test case. This case tests the usage of multiple constructors in the compilation and execution
 *        of a POG. In addition, it tests the cohabitation of more than one POG in the same applications. 
 *
 */

#include "popgroup.ph"
#include <iostream>
#include <assert.h>

int main(int argc, char* argv[]){
  std::cout << "Collective test case n4 started ..." << std::endl; 
  POPGroup group1(10); 
  group1.initialize(2); 

  int g1_r0 = group1[0].get_node_value(); 
  int g1_r1 = group1[1].get_node_value(); 

  assert(g1_r0 == 10); 
  assert(g1_r1 == 10); 
  
  std::cout << "Group 1 - Object 0 - Node value = " << group1[0].get_node_value() << std::endl; 
  std::cout << "Group 1 - Object 1 - Node value = " << group1[1].get_node_value() << std::endl; 
  
  POPGroup group2(11, 2.0); 
  group2.initialize(2); 

  int g2_r0 = group2[0].get_node_value(); 
  int g2_r1 = group2[1].get_node_value(); 
  double g2_d0 = group2[0].get_precision_value(); 
  double g2_d1 = group2[1].get_precision_value(); 
  
  assert(g2_r0 == 11); 
  assert(g2_r1 == 11); 
  assert(g2_d0 == 2.0); 
  assert(g2_d1 == 2.0);     
  
  std::cout << "Group 2 - Object 0 - Node value = " << group2[0].get_node_value() << std::endl; 
  std::cout << "Group 2 - Object 1 - Node value = " << group2[1].get_node_value() << std::endl; 
  std::cout << "Group 2 - Object 0 - Precision value = " << group2[0].get_precision_value() << std::endl; 
  std::cout << "Group 2 - Object 1 - Precision value = " << group2[1].get_precision_value() << std::endl;   

  group1.finalize(); 
  group2.finalize(); 
  std::cout << "Collective test case n4 terminated successfully ..." << std::endl; 
  return 0; 
}
