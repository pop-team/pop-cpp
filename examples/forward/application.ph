#ifndef APPLICATION_H_ 
#define APPLICATION_H_

parclass Application {
public: 
  classuid(1000); 

  Application() @{ od.url("localhost"); }; 
  ~Application(); 
};

#endif /* APPLICATION_H_ */
