#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


parclass POPObject
{
	classuid(1500);

public:
   enum Days { MON, TUE, WED, THU, FRI, SAT, SUN };
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
   sync seq void fromSyncSeq(int sem);

};



#endif /*POPOBJECT_PH_*/
