#include "chat.ph"
#include <unistd.h>

Chat::Chat(POPString machine) {
    printf("Chat object created.\n\nTo contact this chat from a remote machine, use :\n=================================================\n\n");
    printf("popcrun obj.map ./main %s\n\n", GetAccessPoint().GetAccessString().c_str());
}

Chat::~Chat() {
    printf("Chat on machine:%s is being destroyed\n", POPSystem::GetHost().c_str());
    for(int i=0; i<nbContacts; i++) {
        delete contacts[i];
    }
}

void Chat::Print(POPString str1) {
    printf("%s\n",str1.c_str());
}

Chat& Chat::GetRef() {
    return (*this);
}

void Chat::PrintRef(const Chat& ref) {
    pop_accesspoint job(ref.GetAccessPoint());
    printf("%s\n",job.GetAccessString().c_str());
}

void Chat::AddContact(const Chat& contact) {
    pop_accesspoint job;
    printf("Added contact :");
    PrintRef(contact);
    contacts[nbContacts] = new Chat(contact);
    nbContacts++;
}

void Chat::IntroduceMyself() {
    Chat* myRef= new Chat(GetAccessPoint());
    Chat* firstContact = contacts[nbContacts-1];

    firstContact->ForwardContact(*myRef);
    firstContact->AddContact(*myRef);

    delete myRef;
}

void Chat::ForwardContact(Chat& from) {
    for(int i=0; i<nbContacts; i++) {
        try {
            contacts[i]->AddContact(from);
            from.AddContact(contacts[i]->GetRef());
        } catch(std::exception &e){
	    LOG_WARNING("Exception occurs: %s", e.what());
	}
    }
}

void Chat::SendAll(POPString str1) {
    char str2[100];
    sprintf(str2,"<%s>%s",POPSystem::GetHost().c_str(),str1.c_str());
    for(int i=0; i<nbContacts; i++) {
        try {
            contacts[i]->Print(str2);
        } catch(std::exception &e) {
            LOG_WARNING("Exception occurs: %s", e.what());
        }
    }
}

@pack(Chat);
