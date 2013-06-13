#include "popgroup.ph"
#include <iostream>

POPGroup::POPGroup(int node) 
{
  std::cout << "POPGroup created with int: " << node << std::endl;
  _node = node; 
}

POPGroup::POPGroup(int node, double precision)
{
  std::cout << "POPGroup created with int: " << node << " double:" << precision << std::endl;
  _node = node; 
  _precision = precision; 
}

POPGroup::~POPGroup()
{

}

void POPGroup::collective()
{

}

void POPGroup::asynchronous_collective()
{

}

void POPGroup::set_value(int value) 
{

}

int POPGroup::get_node_value()
{
  return _node; 
}

double POPGroup::get_precision_value()
{
  return _precision; 
}

@pack(POPGroup);
