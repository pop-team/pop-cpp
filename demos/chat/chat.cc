#include "chat.ph"
#include <unistd.h>

Chat::Chat(POPString machine)
{
	printf("Chat object created.\n\nTo contact this chat from a remote machine, use :\n=================================================\n\n");
	printf("popcrun obj.map ./main %s\n\n", (const char*)GetAccessPoint().GetAccessString());
}

Chat::~Chat()
{
	printf("Chat on machine:%s is being destroyed\n", (const char*)POPSystem::GetHost());
	for (int i=0;i<nbContacts;i++)
		delete(contacts[i]);
}

void Chat::Print(POPString str1)
{
	printf("%s\n",(const char *)str1);
}

Chat Chat::GetRef()
{
	return Chat(GetAccessPoint());
}

void Chat::PrintRef(const Chat& ref)
{
	paroc_accesspoint job(ref.GetAccessPoint());
	printf("%s\n", (const char*)job.GetAccessString());
}

void Chat::AddContact(const Chat& contact)
{
	paroc_accesspoint job;
	printf("Added contact :");
	PrintRef(contact);
	contacts[nbContacts] = new Chat(contact);
	nbContacts++;
}

void Chat::IntroduceMyself()
{
	Chat* myRef= new Chat(GetAccessPoint());
	Chat* firstContact = contacts[nbContacts-1];

	firstContact->ForwardContact(*myRef);
	firstContact->AddContact(*myRef);

	delete(myRef);
}

void Chat::ForwardContact(Chat& from)
{
	for (int i=0;i<nbContacts;i++)
	{
		try
		{
			contacts[i]->AddContact(from);
			from.AddContact(contacts[i]->GetRef());
		}
		catch (...) {}
	}
}

void Chat::SendAll(POPString str1)
{
	char str2[100];
	sprintf(str2,"<%s>%s",(const char *)POPSystem::GetHost(),(const char *)str1);
	for (int i=0;i<nbContacts;i++) {
		try
		{
			contacts[i]->Print(str2);
		}
		catch (...) {}
	}
}

@pack(Chat);
