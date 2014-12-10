#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


parclass POPObject {
    classuid(1500);

public:
    enum Days { MON, TUE, WED, THU, FRI, SAT, SUN };
    enum Month { JAN=10, FEB=11, MAR=12, APR=14, MAY=15, JUN=16, JUL=17, AUG=18, SEP=19, OCT=20, NOV=21, DEC=22};
    POPObject() @{ od.search(0, 0, 0); };
    ~POPObject();
    sync seq void executeSmthToday(int sem);
    sync seq void executeSmthThisMonth(int sem);
};



#endif /*POPOBJECT_PH_*/
