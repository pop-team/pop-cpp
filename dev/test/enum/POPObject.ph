#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


parclass POPObject
{
	classuid(1500);

public:
   enum Days{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
   sync seq void fromSyncSeq(int sem);

};

#endif /*POPOBJECT_PH_*/
