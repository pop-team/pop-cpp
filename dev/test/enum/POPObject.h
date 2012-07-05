#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


class POPObject
{
public:
   enum Days;
	POPObject();
	~POPObject();
	void fromSyncSeq(int sem);
};

#endif /*POPOBJECT_PH_*/
