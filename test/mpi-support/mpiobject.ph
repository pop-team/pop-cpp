

parclass MPIObject {
public:
  classuid(2100); 
  MPIObject() @{ od.executable("./mpiobject.obj"); }; 
  ~MPIObject(); 

  sync broadcast void mpicalls();
}; 
