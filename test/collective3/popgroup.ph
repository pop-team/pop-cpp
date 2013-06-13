

parclass POPGroup {
public: 
  classuid(3001); 
  POPGroup() @{ od.executable("./popgroup.obj"); }; 
  ~POPGroup(); 

  sync broadcast void collective(); 
  async broadcast void asynchronous_collective(); 

  sync seq void set_value(int value);


}; 
