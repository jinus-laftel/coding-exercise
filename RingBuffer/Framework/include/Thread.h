/**
 * @file	Thread.h
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread
{
public:
	Thread();
	virtual ~Thread();

	virtual void runImpl();
	void start();

private:
	pthread_t mThread;
};

#endif // THREAD_H

