#include <dlfcn.h>
#include <stdio.h>
#include "paroc_buffer_factory.h"
#include "paroc_buffer_factory_finder.h"


int main(int argc, char **argv)
{
	if (argc<2)
	{
		printf("Usage:  parocplugin module0 module2 ...\n");
		return 1;
	}
	paroc_buffer_factory * (*CreateFactory)();

	for (int i=1;i<argc;i++)
	{
		void *handler=dlopen(argv[i],RTLD_NOW| RTLD_LOCAL);
		if (handler==NULL)
		{
			printf("Error on dlopen(%s): %s\n",argv[i],dlerror());
			continue;
		}
		CreateFactory=(paroc_buffer_factory * (*)())dlsym(handler,"ParocBufferFactory");

		if (CreateFactory==NULL)
		{
			printf("Error %s: Can not locate ParocBufferFactory\n",argv[i]);
		}
		else
		{
			paroc_buffer_factory *test=CreateFactory();
			if (test==NULL)
			{
				printf("Error: Fail to create a buffer factory\n");
			}
			else
			{
				paroc_string str;
				test->GetBufferName(str);
				printf("Buffer name:%s\n", (const char *)str);
				test->Destroy();
			}
		}
		dlclose(handler);
	}
	return 0;
}
