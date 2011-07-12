#include "demopopc.ph"

int main(int argc, char** argv)

{
	if (argc<2||atoi(argv[1])==0)
	{
		printf("Usage: popcrun obj.map %s NbObjects machine1, machine2, .... \n", argv[0]);
		return 0;
	}
	else
	{
		int nbObjects = atoi(argv[1]);
		POPCobject** objects=new POPCobject*[nbObjects];

		printf("\nSTART of %s program with %d objects\n", argv[0], nbObjects);

		for (int i = 0; i<argc-2 && i<atoi(argv[1]); i++) {
			if (argv[i+2][0]=='-') {
				// objects created by job manager
				objects[i]=new POPCobject(i+1, 60, 40);
			}
			else
			{
				// objects created on a given hostname
				objects[i]=new POPCobject(i+1, argv[i+2]);
			}
		}
		// The rest is created using hostname=localhost
		for (int i = argc-2; i<nbObjects; i++) objects[i]=new POPCobject(i+1, (POPString)("localhost"));

		// Send IDs to each other
		for (int i=0; i<(nbObjects-1); i++) objects[i]->sendIDto(*(objects[i+1]));
		objects[nbObjects-1]->sendIDto(*(objects[0]));
		objects[nbObjects-1]->wait(2);
		for (int i=0; i<nbObjects; i++) delete objects[i];
		delete objects;
	}
	printf("\nEND of %s program\n", argv[0]);
	return 0;
}
