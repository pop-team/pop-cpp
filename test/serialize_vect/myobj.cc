#include "myobj.ph"
#include <unistd.h>


POPCobject::POPCobject(int newID, int wanted, int minp)
{
	printf("POPCobject with ID=%d created (by JobMgr) on machine:%s\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::POPCobject(int newID, POPString machine)
{
	printf("POPCobject with ID=%d created on machine:%s\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::~POPCobject()
{
	printf("POPCobject:%d on machine:%s is being destroyed\n", iD, (const char*)POPSystem::GetHost());
	iD=-1;
}

void POPCobject::test0(vector<vector<int> > &a, bool print)
{
	if (print && a.size()<20 && a.size()>0 && a[0].size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.size();i++) {
			for (int j =0;j<a[i].size();j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}
}

void POPCobject::test1(vector<int> &a, bool print)
{
	if (print)for (int i =0;i<a.size();i++)a[i]*=2;
	if (print&&a.size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.size();i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
}

void POPCobject::test2(POPintVector1 &a, bool print) {
	if (print&&a.size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.size();i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
}

void POPCobject::test3(vector<string> &a, bool print)
{
	if (print && a.size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.size();i++) {
			printf("%s ", a[i].c_str());
		}
		printf("\n");
	}
}

void POPCobject::test4(vector<double> &a, bool print)
{
	if (print&&a.size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.size();i++) {
			printf("%lf ", a[i]);
		}
		printf("\n");
	}
}

void POPCobject::test5(POPintVector2 &a, bool print) {
	if (print&&a.vect.size()<20) {
		printf("Print vector :");
		for (int i =0;i<a.vect.size();i++) {
			printf("%d ", a.vect[i]);
		}
		printf("\n");
	}
}


POPintVector1::POPintVector1() {
	ser=0;
}

POPintVector1::~POPintVector1() {};


void POPintVector1::Serialize(POPBuffer &buf, bool pack)
{
	if (ser==0) {
		int a;
		long vsize;
		vector<int>::iterator iter;
		if (pack)
		{
			vsize=size();
			buf.Pack(&vsize,1);
			for (iter=begin(); iter!=end(); iter++)
			{
				a = *iter;
				buf.Pack(&a,1);
			}
		}
		else
		{
			buf.UnPack(&vsize,1);
			clear();
			for (long i=0; i<vsize; i++)
			{
				buf.UnPack(&a,1);
				push_back(a);
			}
		}

	} else if (ser==1) {

		if (pack)
		{
			int n=size();
			buf.Pack(&n,1);
			buf.Pack(&(*this)[0],n);
		}
		else
		{
			int n=0;
			buf.UnPack(&n,1);
			resize(n);
			buf.UnPack(&(*this)[0],n);
		}
	} else {
		// This does NOT work
		POPException::paroc_throw("Error : This marshalling method does not work (2)!!");
		/*if (pack)
		{
			assert(dynamic_cast<vector<int>*>(this)!=NULL);
			buf.Pack(dynamic_cast<vector<int>*>(this),1);
		}
		else
		{
			buf.UnPack(dynamic_cast<vector<int>*>(this),1);
		}*/
	}
}

POPintVector2::POPintVector2() {
	ser=0;
}

POPintVector2::~POPintVector2() {};


void POPintVector2::Serialize(POPBuffer &buf, bool pack)
{
	if (ser==0) {
		int a;
		long vsize;
		vector<int>::iterator iter;
		if (pack)
		{
			vsize=vect.size();
			buf.Pack(&vsize,1);
			for (iter=vect.begin(); iter!=vect.end(); iter++)
			{
				a = *iter;
				buf.Pack(&a,1);
			}
		}
		else
		{
			buf.UnPack(&vsize,1);
			vect.clear();
			for (long i=0; i<vsize; i++)
			{
				buf.UnPack(&a,1);
				vect.push_back(a);
			}
		}

	} else if (ser==1) {
		if (pack)
		{
			int n=vect.size();
			buf.Pack(&n,1);
			//printf("ser %d %p (%p)\n",n,&(*this)[0],this);
			buf.Pack(&vect[0],n);
		}
		else
		{
			int n=0;
			buf.UnPack(&n,1);
			vect.resize(n);
			buf.UnPack(&vect[0],n);
		}
	} else {
		if (pack)
		{
			buf.Pack(&vect,1);
		}
		else
		{
			buf.UnPack(&vect,1);
		}
	}
}

@pack(POPCobject);
