#include <stdio.h>

bool onNewConnection(void *data, paroc_connection *conn)
{
	int *t=(int *)data;
	(*t)++;
	paroc_combox *cb=conn->GetCombox();
	char chr=0;
	printf("Connections: %d\n",*t);
	return true;
}

bool onCloseConnection(void *data, paroc_connection *conn)
{
	int *t=(int *)data;
	(*t)--;
	printf("Connections: %d\n",*t);
	return (*t!=0);
}

int main(int argc, char **argv)
{
	if (argc<=1)
	{
		printf("Usage: combox_server <protocol>\n");
		return 1;
	}
	paroc_combox_factory *fact=paroc_combox_factory::GetInstance();

	paroc_combox *server=fact->Create(argv[1]);

	if (server==NULL)
	{
		printf("Error: %s: unknown protocol\n", argv[1]);
		return 1;
	}

	server->Create(0,true);

	paroc_string addr;
	if (!server->GetUrl(addr))
	{
		server->Destroy();
		printf("Error: can not get listening address\n");
		return  1;
	}

	printf("SERVER ACCESS POINT: %s\n",(const char *)addr);
	int count=0;

	server->SetCallback(COMBOX_NEW, onNewConnection,&count);
	server->SetCallback(COMBOX_CLOSE, onCloseConnection,&count);
	//  server->SetTimeout(30000);
	int n;
	paroc_connection *peer=NULL;


	paroc_buffer_factory *bf=server->GetBufferFactory();
	paroc_buffer *buffer=bf->CreateBuffer();
	paroc_string name;
	int status;
	paroc_array<char> buf;

	while ((peer=server->Wait())!=NULL)
	{
		paroc_buffer_factory *bf=peer->GetBufferFactory();
		buffer=bf->CreateBuffer();
		if (buffer->Recv(peer))
		{
			int status;
			buffer->UnPack(&status,1);
			if (status<=-1)
			{
				buffer->UnPack(&name,1);
				bf=paroc_buffer_factory_finder::GetInstance()->FindFactory(name);
				if (bf==NULL)
				{
					printf("Error: can not find encoding %s\n", (const char *)name);
					status=0;
				}
				else
				{
					printf("Using encoding %s\n", (const char *)name);
					peer->SetBufferFactory(bf);
				}
				buffer->Reset();
				buffer->Pack(&status,1);
				if (!buffer->Send(peer))
				{
					printf("Can not send back encoding status (%d)\n", status);
				}
			}
			else
			{

				buf.SetSize(status);
				int count;
				buffer->UnPack(&count,1);
				buffer->UnPack(buf, status);
				count++;
				buffer->Reset();
				buffer->Pack(&status,1);
				buffer->Pack(&count,1);
				buffer->Pack(buf,status);
				if (!buffer->Send(peer))
				{
					printf("Can not send back message\n");
				}
			}
		}
		buffer->Destroy();
	}
	server->Destroy();
	printf("Client closed the connection\n");
	return 0;
}
