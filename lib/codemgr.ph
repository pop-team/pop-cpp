#ifndef CODEMGR_PH
#define CODEMGR_PH

#include "paroc_array.h"
#include "paroc_service_base.ph"

typedef char string256[256];
struct codedata
{
  codedata(){};
  string256 platform;
  string256 codefile;
};

struct codedb
{
  codedb() {};
  string256 objname;
  paroc_array<codedata> platform;
};

typedef paroc_array<codedb> CodeDBArray;


parclass CodeMgr: virtual public paroc_service_base
{
public:
	CodeMgr(const paroc_string &challenge);
	~CodeMgr();
	seq async sync void RegisterCode(const paroc_string &objname, const paroc_string &platform, const paroc_string &codefile);
	seq sync int QueryCode(const paroc_string &objname, const paroc_string &platform, [out] paroc_string &codefile);
	seq sync int GetPlatform(const paroc_string &objname, [out]  paroc_string &platform);
	
	classuid(2);

protected:
	CodeDBArray info;
};


#endif
