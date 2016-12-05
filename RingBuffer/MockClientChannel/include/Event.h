/**
 * @file	Event.h
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef EVENT_H
#define EVENT_H

enum EventType
{
	EVENT_NEWCONNECT,
	EVENT_LOGOUT,
	EVENT_MOVE,
	EVENT_CHAT,
	EVENT_TRADE,
	EVENT_TYPE_MAX
};

struct Event
{
	Event * mNextEvent;
	long mEventTime;
	long mClientID;
	EventType mType;
};

#endif // EVENT_H

