#include <timer.h>
#include <stdio.h>

#define LOOP 10
#define MSGSIZE 7111

int main(int argc, char **argv)
{
	if (argc<2)
	{
		printf("Usage: combox_test <address>\n");
		return 1;
	}
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

	client->Create(0,false);
	if (!client->Connect(argv[1]))
	{
		client->Destroy();
		printf("Error: can not connect to %s\n", argv[1]);
		return  1;
	}

	printf("Connected!\n");

	char buf[MSGSIZE];
	char str[MSGSIZE];

	int n;
	Timer timer;
	timer.Start();

	while (fgets(str, MSGSIZE-1,stdin)!=NULL)
	{
		int len=strlen(str);
		while (len>0 && str[len-1]=='\n' || str[len-1]=='\r')
		{
			len--;
			str[len]=0;
		}
		strcat(str,"\r\n");
		len+=2;
		if (client->Send(str,len)!=len)
		{
			printf("Send error\n");
			break;
		}
		fprintf(stdout,"SENT[%d]: %s",len, str);
	}
	client->SetTimeout(300000);

	fprintf(stdout,"NOW WAITING FOR REPLY\n");
	while (1)
	{
		int n=client->Recv(str,MSGSIZE-1);
		if (n<=0)
		{
			break;
		}
		str[n]=0;
		fprintf(stdout,str);
		fflush(stdout);
	}

	client->Destroy();

	return 0;
}
