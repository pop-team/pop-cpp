#include "radio.ph"

Radio::Radio()
{
  printf("Radio created\n"); 
}

Radio::~Radio()
{

}

void Radio::set_application(Application& a)
{
  _application = &a;
  printf("Set Application %s\n", _application->GetAccessPoint().GetAccessString());  
}

Application& Radio::get_application() {
  return (*_application);   
}


@pack(Radio); 
