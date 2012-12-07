#ifndef RADIO_H_
#define RADIO_H_

#include "application.ph"

parclass Radio {
public:
  classuid(1002); 

  Radio() @{ od.url("localhost"); };
  ~Radio();

  sync conc void set_application([in] Application& a); 
  sync conc Application& get_application(); 


private: 
  Application* _application;
};

#endif /* RADIO_H_ */

