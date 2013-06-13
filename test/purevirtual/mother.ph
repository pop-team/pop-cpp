#ifndef MOTHER_H
#define MOTHER_H

parclass Mother
{
public:
	classuid(1200);
	Mother() @{ od.node(1); od.executable("child.obj"); };
	~Mother();
	sync seq virtual void method_pv()=0; // Declare pure virtual method
};

#endif /* MOTHER_H */
