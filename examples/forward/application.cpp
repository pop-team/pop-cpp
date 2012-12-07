#include "application.ph"

Application::Application()
{
  printf("Application created %s\n", GetAccessPoint().GetAccessString());   
}

Application::~Application()
{

}

@pack(Application)

