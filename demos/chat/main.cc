#include "chat.ph"
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	// Create the local chat object
	Chat o1("localhost");

	if (argc>1)
	{
		printf("Try to connect to the remote chat object %s\n", argv[1]);
		paroc_accesspoint job;
		job.SetAccessString(argv[1]);
		Chat* firstContact = new Chat(job);
		o1.AddContact(*firstContact);
		o1.IntroduceMyself();

		delete (firstContact);
	}
	printf("===============================================\n");
	printf("type 'q' to quit\n");
	char msg[100]="";

	bool running=true;
	while (running)
	{
		cin.getline(msg, 100);
		if (!strcmp(msg,"q"))running=false;
		else o1.SendAll(msg);
	}
	return 0;
}
