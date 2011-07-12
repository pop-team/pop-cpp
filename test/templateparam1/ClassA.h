#ifndef _CLASSA_H_
#define _CLASSA_H_

template <class C> class ClassA
{
public:
	ClassA();
	~ClassA();
	C* GetData();
	void SetData(C d);

private:
	C x;
};

#endif
