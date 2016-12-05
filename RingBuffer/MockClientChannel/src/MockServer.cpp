/**
 * @file	MockServer.cpp
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#include "MockServer.h"
#include "Event.h"

#include <assert.h>

const long nSec = 1000000000;

const long moveInterval_nSec = nSec / 2;
const long chatInterval_nSec = nSec;
const long tradeInterval_nSec = nSec;

MockServer::MockServer( long clientInterval_nSec )
	: mNextEvent(0)
	, mNextClientID(0)
	, mClientCount(0)
	, mIdleCount(0)
	, mMoveCount(0)
	, mChatCount(0)
	, mTradeCount(0)
	, mClientInterval_nSec( clientInterval_nSec )
	, mLogoutCount(0)
	, mExpectedLogoutCount(0)
	, mLogoutEventTime(0)
{
	Event * firstEvent = new Event;
	firstEvent->mEventTime = 0;
	firstEvent->mType = EVENT_NEWCONNECT;
	addEvent( firstEvent );
}

void MockServer::addEvent( Event * event )
{
	long eventTime = event->mEventTime;

	if( ! mNextEvent )
	{
		event->mNextEvent = 0;
		mNextEvent = event;
	}
	else if( eventTime < mNextEvent->mEventTime )
	{
		event->mNextEvent = mNextEvent;
		mNextEvent = event;
	}
	else
	{
		Event * prevEvent = mNextEvent;
		Event * nextEvent = prevEvent->mNextEvent;
		while( nextEvent && nextEvent->mEventTime < eventTime )
		{
			prevEvent = nextEvent;
			nextEvent = nextEvent->mNextEvent;
		}

		prevEvent->mNextEvent = event;
		event->mNextEvent = nextEvent;
	}
}

void MockServer::process( long currentTime )
{
	Event * event = getTimeoutEvent( currentTime );

	if( event )
		processEvent( event, currentTime );
	else
		mIdleCount++;
}

void MockServer::processEvent( Event * event, long currentTime )
{
	Event * newEvent = 0;

	switch( event->mType )
	{
	case EVENT_NEWCONNECT :
		newEvent = new Event;
		newEvent->mClientID = mNextClientID ++;
		setRandomEvent( newEvent, currentTime );
		addEvent( newEvent );

		event->mEventTime = currentTime + ( ( currentTime % 9 ) * mClientInterval_nSec / 4 );
		addEvent( event );
		mClientCount ++;
		break;
	case EVENT_LOGOUT :
		delete event;
		mClientCount --;
		mLogoutCount ++;
		break;
	case EVENT_MOVE :
		setRandomEvent( event, currentTime );
		addEvent( event );
		break;
	case EVENT_CHAT :
		setRandomEvent( event, currentTime );
		addEvent( event );
		break;
	case EVENT_TRADE :
		setRandomEvent( event, currentTime );
		addEvent( event );
		break;
	default :
		break;
	}
}

void MockServer::setRandomEvent( Event * event, long currentTime )
{
	assert( event );

	switch( ( currentTime + 1 ) % 4 )
	{
	case 0:
		if( mLogoutCount < mExpectedLogoutCount )
		{
			event->mType = EVENT_LOGOUT;
			event->mEventTime = currentTime + ( currentTime % 1024 );
			break;
		}
	case 1:
		event->mType = EVENT_MOVE;
		event->mEventTime = currentTime + ( ( currentTime % 9 ) * moveInterval_nSec / 4 );
		mMoveCount ++;
		break;
	case 2:
		event->mType = EVENT_CHAT;
		event->mEventTime = currentTime + ( ( currentTime % 9 ) * chatInterval_nSec / 4 );
		mChatCount ++;
		break;
	case 3:
		event->mType = EVENT_TRADE;
		event->mEventTime = currentTime + ( ( currentTime % 9 ) * tradeInterval_nSec / 4 );
		mTradeCount ++;
		break;
	}
}

Event * MockServer::getTimeoutEvent( long timeStamp )
{
	Event * event = mNextEvent;

	if( event && event->mEventTime < timeStamp )
	{
		mNextEvent = event->mNextEvent;

		return event;
	}

	return 0;
}

