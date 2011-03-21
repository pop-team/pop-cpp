#include <stdio.h>
#include <timer.h>
#include <string.h>
#include <unistd.h>

parclass Pong
{
public:
	classuid(1500);
	Pong(POPString enc, POPString prot) @{ od.power(200,50); od.encoding(enc); od.protocol(prot); };
	async void pingAC([in, size=sz] char *data, int sz);
	sync  void pingSC([in,out, size=sz] char *data, int sz);

	async void pingAInt([in, size=sz] int *data, int sz);
	sync  void pingSInt([in,out, size=sz] int *data, int sz);

	async void pingAF([in, size=sz] float *data, int sz);
	sync  void pingSF([in,out, size=sz] float *data, int sz);

	void GetMachine([out, size=256] char *pong);

	mutex sync int Reset();
	mutex int GetCount();
protected:
	int count;
};

#define NTEST 10
#define NLOOP 5000
#define STARTSZ 7500
#define ENDSZ 8000

parclass Ping
{
	classuid(1501);
public:
	Ping(POPString enc, POPString prot, int p) @{ od.power(p);} ;
	sync void Run();
	void GetResults([out,size=NTEST] int *sizes, [out,size=NTEST] double *chrA, [out,size=NTEST] double *chrS, [out,size=NTEST] double *iA, [out,size=NTEST] double *iS, [out,size=NTEST] double *fA,  [out,size=NTEST] double *fS   );
	void GetMachines([out,size=256] char *ping, [out, size=256] char *pong);
protected:
	Pong test;
	double charA[NTEST], charS[NTEST],intA[NTEST],intS[NTEST], floatA[NTEST], floatS[NTEST];
};
