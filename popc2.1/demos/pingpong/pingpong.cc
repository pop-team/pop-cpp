#include "pingpong.ph"



Pong::Pong(POPString enc, POPString prot)
{
	rprintf("Pong on %s\n",(const char *)POPSystem::GetHost());
	if (enc!=NULL) rprintf("Ping-pong encoding: %s\n",(const char *)enc);
	if (prot!=NULL) rprintf("Ping-pong protocol: %s\n",(const char *)prot);
	count=0;
}

void Pong::pingAC(char *data, int sz)
{
	//  usleep(40000);
	mutex { count++;}
}

void Pong::pingSC(char *data, int sz)
{
	count++;
}

void Pong::pingAInt(int *data, int sz)
{
	mutex { count++; }
}

void Pong::pingSInt(int *data, int sz)
{
	count++;
}

void Pong::pingAF(float *data, int sz)
{
	mutex { count++; }
}

void Pong::pingSF(float *data, int sz)
{
	count++;
}

void Pong::GetMachine(char *pong)
{
	strcpy(pong, POPSystem::GetHost());
}
int Pong::Reset()
{
	count=0;
	return 1;
}

int Pong::GetCount()
{
	return count;
}


Ping::Ping(POPString enc, POPString prot, int p): test(enc, prot)
{
	rprintf("Ping on %s\n", (const char *)POPSystem::GetHost());
}

void Ping::Run()
{
	Timer timer;
	int count;
	timer.Start();

	sleep(1);

	timer.Reset();
	char tmpchr[ENDSZ*4];
	float tmpfloat[ENDSZ];
	int tmpint[ENDSZ];

	for (int i=0;i<ENDSZ*4;i++) tmpchr[i]=rand()%255;
	for (int i=0;i<ENDSZ;i++) tmpint[i]=rand();
	for (int i=0;i<ENDSZ;i++) tmpfloat[i]=rand()/17.0;


	int sz=STARTSZ;
	for (int i=0;i<NTEST;i++)
	{
		sz=4*(ENDSZ*i/(NTEST-1));
		if (sz==0) sz=1;
		//Asynchronous invocation on  CHAR
		rprintf("Test #%d on invocation of CHAR message\n",i);
		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingAC(tmpchr,sz);
		if ((count=test.GetCount())!=NLOOP)
		{
			charA[i]=0;
			rprintf("Test on async Invoke(char) fail (%d/%d)\n", count, NLOOP);
		} else charA[i]=sz*NLOOP/timer.Elapsed()/1024.0;

		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingSC(tmpchr,sz);
		charS[i]=2*sz*NLOOP/timer.Elapsed()/1024.0;

		sz=ENDSZ*i/(NTEST-1);
		if (sz==0) sz=1;
		//Test Invoke on INT....
		rprintf("Test #%d on invocation of INT message\n",i);
		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingAInt(tmpint,sz);
		if ((count=test.GetCount())!=NLOOP)
		{
			intA[i]=0;
			rprintf("Test on async Invoke(Int) fail (%d/%d)\n", count, NLOOP);
		} else intA[i]=NLOOP*sz*4/timer.Elapsed()/1024.0;

		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingSInt(tmpint,sz);
		intS[i]=NLOOP*sz*8/timer.Elapsed()/1024.0;

		rprintf("Test #%d on invocation of FLOAT message\n",i);
		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingAF(tmpfloat,sz);
		if ((count=test.GetCount())!=NLOOP)
		{
			floatA[i]=0;
			rprintf("Test on async Invoke(float) fail (%d/%d)\n", count, NLOOP);
		} else floatA[i]=NLOOP*sz*4/timer.Elapsed()/1024.0;

		test.Reset();
		sleep(1);
		timer.Reset();
		for (int j=0;j<NLOOP;j++) test.pingSF(tmpfloat,sz);
		floatS[i]=NLOOP*sz*8/timer.Elapsed()/1024.0;

	}

}
void Ping::GetResults(int *sizes, double *chrA, double *chrS, double *iA,  double *iS,  double *fA,  double *fS )
{
	memcpy(chrA,charA,sizeof(double)*NTEST);
	memcpy(chrS,charS,sizeof(double)*NTEST);

	memcpy(iA,intA,sizeof(double)*NTEST);
	memcpy(iS,intS,sizeof(double)*NTEST);

	memcpy(fA,floatA,sizeof(double)*NTEST);
	memcpy(fS,floatS,sizeof(double)*NTEST);

	sizes[0]=1;
	for (int i=1;i<NTEST;i++) sizes[i]=4*i*ENDSZ/(NTEST-1);
}

void Ping::GetMachines(char *ping, char *pong)
{
	strcpy(ping,POPSystem::GetHost());
	test.GetMachine(pong);
}


@pack(Ping, Pong);


