/**
 * @file	Buffer.h
 * @brief	Buffer for event stream processing
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef BUFFER_H
#define BUFFER_H

#include "Platform.h"

/**
 * @class	Event
 */
class Event
{
	enum Type
	{
		EVENT_A,
		EVENT_B,
		EVENT_C,
		MAX_EVENT_ID
	};

public:
	inline Type type() { return mType; }
	inline void type(Type type) { mType = type; }

private:
	Type mType;
	char data[128];
};

#endif // BUFFER_H

