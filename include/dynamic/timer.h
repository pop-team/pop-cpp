/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 01/01/2005
 * @brief Timer declaration
 *
 *
 */

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


