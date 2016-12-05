/**
 * @file	RingBuffer.h
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Util.h"
#include "Platform.h"

typedef unsigned long Cursor;

/**
 * @class	RingBuffer
 * @brief	Data structure for message passing between threads
 *	Minimum SCALE value is 3, and recommended value is 5~6
 *
 *	SCALE	Number of buffers
 *	4		16
 *	5		32
 *	6		64
 */
template<typename BufferType, unsigned SCALE>
class RingBuffer
{
	// Buffer state ID starts from 0
	//	0 means this buffer is free for any producer.
	//	1 means this buffer is reserved for specific producer.
	//	2+ is user-defined state, and follow this StateProperty
	struct BufferInfo
	{
		// ASSUME : cache line size is less then 64 byte
		long mStateID;
		long mOwnerID;
		long reserved_padding_64[6];
	};

public:
	RingBuffer()
		: mEventHandlerCount(1)
//		, mSequence(ULONG_MAX - 63)		// Uncomment this for unit test
		{}
	~RingBuffer() {}

	// Setup : get Event Handler ID and init cursor(just unsigned long 0)
	//	(Event Handler ID 0 is reserved by publisher)
	inline long getEventHandlerID( Cursor *cursor )
	{
		*cursor = 0;
		return INC64(&mEventHandlerCount);
	}

	////////////////////////////////////////////////////////////////
	// Publisher
	////////////////////////////////////////////////////////////////
	// Step 1 : get sequence by next()
	inline unsigned long next() { return next(&mSequence); }
	// Step 2 : check that buffer available
	inline bool isAvailable( unsigned long sequence ) { return isAvailable( sequence, 0 ); }
	// Step 3 : get buffer (same as event handler's one)
//	inline BufferType *get( unsigned long sequence )
	// Step 4 : release
	inline void release( unsigned long sequence ) { return release( sequence, 0 ); }


	////////////////////////////////////////////////////////////////
	// Event Handler
	////////////////////////////////////////////////////////////////
	// Step 1 : get sequence by next()
	inline unsigned long next( Cursor *cursor )
	{
		return INC64(cursor);
	}

	// Step 2 : poll until buffer available
	inline bool isAvailable( unsigned long sequence, long eventHandlerID )
	{
		return mInfo[sequence].mOwnerID == eventHandlerID;
	}

	// Step 3 : get buffer
	inline BufferType *get( unsigned long sequence )
	{
		return mBuffer[sequence & Size<SCALE>::mask];
	}

	// Step 4 : release
	inline void release( unsigned long sequence, long eventHandlerID )
	{
		long ownerID = mInfo[sequence].mOwnerID;
		CAS64( &mInfo[sequence].mOwnerID, ownerID, (ownerID + 1) % mEventHandlerCount );
	}

private:
	// ASSUME : cache line size is less then 64 byte
	long mEventHandlerCount;
	long reserved_padding_64a[7];
	unsigned long mSequence;		// for publisher
	long reserved_padding_64b[7];
	BufferInfo mInfo[Size<SCALE>::value];
	BufferType mBuffer[Size<SCALE>::value];
};

#endif // RINGBUFFER_H

