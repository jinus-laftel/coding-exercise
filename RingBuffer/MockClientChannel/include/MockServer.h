/**
 * @file	MockServer.h
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include "Event.h"

class MockServer
{
public:
	MockServer( long clientInterval_nSec );

	void addEvent( Event * event );
	void process( long currentTime );
	inline long clientCount() { return mClientCount; }
	inline long logoutCount() { return mLogoutCount; }
	inline long idleCount() { long idleCount = mIdleCount; mIdleCount = 0; return idleCount; }
	inline long moveCount() { long moveCount = mMoveCount; mMoveCount = 0; return moveCount; }
	inline long chatCount() { long chatCount = mChatCount; mChatCount = 0; return chatCount; }
	inline long tradeCount() { long tradeCount = mTradeCount; mTradeCount = 0; return tradeCount; }
	inline void expectLogoutCount( long count ) { mExpectedLogoutCount = count; }

private:
	void processEvent( Event * event, long currentTime );
	void setRandomEvent( Event * event, long currentTime );
	Event * getTimeoutEvent( long timeStamp );

	Event * mNextEvent;
	long mNextClientID;
	long mClientCount;
	long mIdleCount;
	long mMoveCount;
	long mChatCount;
	long mTradeCount;
	long mClientInterval_nSec;
	long mLogoutCount;
	long mExpectedLogoutCount;
	long mLogoutEventTime;
};

#endif // MOCKSERVER_H

