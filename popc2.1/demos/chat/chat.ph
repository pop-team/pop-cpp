#ifndef CHAT_PH_
#define CHAT_PH_

parclass Chat
{
	classuid(1500);

public:
	Chat(POPString machine) @{od.url(machine);};
	async conc void Print(POPString str1);
	async conc void SendAll(POPString str1);
	sync seq void AddContact(const Chat& contact);
	sync seq void ForwardContact(Chat& from);
	sync conc void IntroduceMyself();
	sync conc Chat GetRef();
	sync conc void PrintRef(const Chat& ref);
	~Chat();
private:
	Chat* contacts[100];
	int nbContacts;
};

#endif
