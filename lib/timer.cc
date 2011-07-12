/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: the timer implementation, used by the runtime
 */


#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

int debuglevel=2;

Timer::Timer()
{
	isRunning=false;
	start_point=0;
	elapsed=0;
}

void Timer::Start()
{
	if (!isRunning)
	{
		isRunning=true;
		start_point=GetCurrentTime();
	}
}

void Timer::Stop()
{
	if (isRunning)
	{
		elapsed+=GetCurrentTime()-start_point;
		isRunning=false;
	}
}

void Timer::Reset()
{
	start_point=GetCurrentTime();
	elapsed=0;
}

double Timer::Elapsed()
{
	if (isRunning)
	{
		return elapsed+GetCurrentTime()-start_point;
	}
	return elapsed;
}

double Timer::GetCurrentTime()
{
	timeval tp;
	gettimeofday(&tp,NULL);
	double t=tp.tv_sec+double(tp.tv_usec)*1.0E-6;
	return t;
}
