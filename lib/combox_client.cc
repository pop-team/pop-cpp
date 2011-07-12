#include <timer.h>
#include <stdio.h>
#include <signal.h>

#define LOOP 10
#define MSGSIZE 7111

int main(int argc, char **argv)
{
	if (argc<2)
	{
		printf("Usage: combox_client <address> [encoding]\n");
		return 1;
	}
	signal(SIGPIPE, SIG_IGN);

	paroc_combox_factory *fact=paroc_combox_factory::GetInstance();

	char prot[32];
	char *tmp;
	if ((tmp=strstr(argv[1],"://"))==NULL)
	{
		strcpy(prot,"socket");
	}
	else
	{
		*tmp=0;
		strcpy(prot,argv[1]);
		*tmp=':';
	}
	paroc_combox *client=fact->Create(prot);

	if (client==NULL)
	{
		printf("Error: %s: unknown protocol\n", prot);
		return 1;
	}

	paroc_buffer_factory *bf=client->GetBufferFactory();
	paroc_buffer *buffer=bf->CreateBuffer();
	paroc_string name;
	if (argc>2)
	{
		name=argv[2];
		bf=paroc_buffer_factory_finder::GetInstance()->FindFactory(name);
		if (bf==NULL)
		{
			printf("Error: can not find encoding %s\n", argv[2]);
			return 1;
		}
	}
	else bf->GetBufferName(name);


	client->Create(0,false);
	if (!client->Connect(argv[1]))
	{
		client->Destroy();
		printf("Error: can not connect to %s\n", argv[1]);
		return  1;
	}

	printf("Connected!\n");



	//Negotiate protocol...
	printf("Setting encoding to %s\n", (const char *)name);
	paroc_message_header h1(0,0,0,"Encoding");
	int status=-1;
	buffer->SetHeader(h1);

	buffer->Pack(&status,1);
	buffer->Pack(&name,1);
	if (!buffer->Send(*client))
	{
		printf("Error: send buffer\n");
		client->Destroy();
		return 1;
	}

	buffer->Reset();
	if (!buffer->Recv(*client))
	{
		printf("Error: receive buffer\n");
		client->Destroy();
		return 1;
	}

	buffer->UnPack(&status,1);
	if (status==-1)
	{
		printf("Use encoding: %s\n",(const char *)name);
		buffer=bf->CreateBuffer();
		buffer->SetHeader(h1);
	}
	else
	{
		printf("Encoding %s not supported\n",(const char *)name);
	}

	status=1;

	char buf[MSGSIZE];
	int count=0;

	int n;
	Timer timer;
	timer.Start();

	for (int i=0;i<LOOP;i++)
	{
		buffer->Reset();
		buffer->Pack(&status,1);
		buffer->Pack(buf, MSGSIZE);
		if (!buffer->Send(*client))
		{
			printf("Error: can not send the message\n");
			client->Destroy();
			return 1;
		}
		buffer->Reset();
		if (!buffer->Recv(*client))
		{
			printf("Error: can not send the message\n");
			client->Destroy();
			return 1;
		}
	}
	timer.Stop();

	printf("Send %d message of %d bytes each to %s in %g seconds (%g MB/s)\n", LOOP, MSGSIZE,argv[1],timer.Elapsed(),2.0*LOOP*MSGSIZE/(timer.Elapsed()*1024.0*1024.0));

	client->Destroy();

	return 0;
}
