#ifndef POPCOBJECT_PH_
#define POPCOBJECT_PH_

#include <timer.h>
#include <vector>
#include <string>

using namespace std;

class POPintVector1;
class POPintVector2;

parclass POPCobject
{
	classuid(1500);

	public:
		POPCobject(int newID, int wanted, int minp) @{od.power(wanted, minp);};
		POPCobject(int newID, POPString machine) @{od.url(machine);};
		~POPCobject();

		sync seq void test0(vector<vector<int>> &a, bool print);
		sync seq void test1(vector<int> &a, bool print);
		sync seq void test2(POPintVector1 &a, bool print);
		sync seq void test3(vector<string> &a, bool print);
		sync seq void test4(vector<double> &a, bool print);
		sync seq void test5(POPintVector2 &a, bool print);
	private:
		int iD;
};


class POPintVector1 : public POPBase, public vector<int>
{
	public:
		POPintVector1();
		~POPintVector1();
		virtual void Serialize(POPBuffer &buf, bool pack);
		int ser;
};

class POPintVector2 : public POPBase
{
	public:
		POPintVector2();
		~POPintVector2();
		virtual void Serialize(POPBuffer &buf, bool pack);
		int ser;
		vector<int> vect;
};






#endif /*POPCOBJECT_PH_*/
