/**
 * @file	Thread.cpp
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#include "Thread.h"

static void * runThread( void * pData )
{
	Thread * pThread = (Thread *)pData;
	pThread->runImpl();

	return pData;
}

Thread::Thread()
{
}

Thread::~Thread()
{
}

void Thread::start()
{
	pthread_create( &mThread, NULL, runThread, this );
}

