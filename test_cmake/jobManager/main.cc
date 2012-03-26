#include "POPCobject.ph"

int main(int argc, char** argv)
{
	printf("JobManager: Starting test...\n");
	bool ok=true;

	try  {POPCobject obj1;}
	catch (POPException *e)
		{printf("JobManager: test failed on object creation: default\n"); ok=false;}

	try  {POPCobject obj2(1,"localhost");}
	catch (POPException *e)
		{printf("JobManager: test failed on object creation: URL\n"); ok=false;}

	try  {POPCobject obj3(2, 40.2);}
	catch (POPException *e)
		{printf("JobManager: test failed on object creation: Power\n"); ok=false;}

	try  {POPCobject obj4(3, 10);}
	catch (POPException *e)
		{printf("JobManager: test failed on object creation: Memory\n"); ok=false;}

	try  {POPCobject obj5(4);}
	catch (POPException *e)
		{printf("JobManager: test failed on object creation: Protocol\n"); ok=false;}

	if (ok) printf("JobManager: test succeeded, destroying objects...\n");
	return 0;
}
