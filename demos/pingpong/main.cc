#include "pingpong.ph"

double charA[NTEST], charS[NTEST],intA[NTEST],intS[NTEST], floatA[NTEST], floatS[NTEST];
int sizes[NTEST];

int main(int argc, char **argv)
{
	POPString enc;
	POPString prot;
	char m1[256],m2[256];
	char *t=POPUtils::checkremove(&argc, &argv,"-encoding=");
	if (t!=NULL) enc=t;

	t=POPUtils::checkremove(&argc, &argv,"-protocol=");
	if (t!=NULL) prot=t;

	Ping tt(enc,prot, 50);
	fprintf(stderr,"Running the tests now...\n");
	tt.Run();
	fprintf(stderr,"...done\n");

	tt.GetMachines(m1,m2);

	tt.GetResults(sizes,charA,charS,intA,intS,floatA,floatS);

	printf("\nPing-pong results between %s and %s\n\nMSG\tACHAR\tSCHAR\tAINT\tSINT\tAFLOAT\tSFLOAT\n",m1,m2);
	for (int i=0;i<NTEST;i++)
	{
		printf("%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",sizes[i],charA[i],charS[i],intA[i],intS[i],floatA[i],floatS[i]);
	}
	return 0;
}
