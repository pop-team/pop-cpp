#ifndef _X_H_
#define _X_H_

class X : public POPBase
{
public:
	X();
	~X();
	int GetIdent();
	void SetIdent(int i);
	virtual void Serialize(POPBuffer &buf, bool pack);


private:
	int ident;
};

#endif
