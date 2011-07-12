#ifndef _X_H_
#define _X_H_

class X : public POPBase
{
public:
	X();
	~X();
	int GetValue();
	void SetValue(int i);
	virtual void Serialize(POPBuffer &buf, bool pack);


private:
	int value;
};

#endif
