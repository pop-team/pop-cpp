#ifndef _PAROC_SYSTEM_H
#define _PAROC_SYSTEM_H
#include <paroc_accesspoint.h>

#define DEFAULTPORT  2711

class AppCoreService;

class paroc_system
{
 public: 
  paroc_system();
  ~paroc_system();

  static bool Initialize(int *argc,char ***argv);//only for the main...
  static void Finalize(bool normalExit); //only for the main...

  static paroc_string GetHost();
  static paroc_string GetIP();  
  static int GetIP(const char *hostname, int *iplist, int listsize);
  static int GetIP(int *iplist, int listsize);
  
  static void perror(const char *msg);

 public:
  static paroc_accesspoint appservice;
  static paroc_accesspoint jobservice;
  static paroc_string platform;

 private:
  static char *paroc_errstr[13];

 private:

  static AppCoreService *CreateAppCoreService(char *codelocation);

  static AppCoreService *mgr;
  static paroc_string challenge;

};


#endif
