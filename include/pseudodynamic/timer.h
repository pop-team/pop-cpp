#ifndef PAROCTIMER_H
#define PAROCTIMER_H



class Timer
{
public:
	Timer();
	void Start();
	void Stop();
	void Reset();
	double Elapsed();
protected:
	virtual double GetCurrentTime();

	double start_point;
	double elapsed;
	bool isRunning;
};

#endif


