#ifndef POP_OBJECT_H_
#define POP_OBJECT_H_

parclass POPObject {
	classuid(1500);

public:
	POPObject() @{ od.node(0); od.executable("./popobject.obj"); };
	~POPObject();

	sync seq void create_group();
	
};

#endif /* POP_OBJECT_H_ */ 
