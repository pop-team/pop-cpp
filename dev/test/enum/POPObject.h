#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


class POPObject
{
public:
   enum Days{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
	POPObject();
	~POPObject();
	void fromSyncSeq(int sem);
};

#endif /*POPOBJECT_PH_*/
