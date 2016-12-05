/**
 * @file	RingBufferTest.cpp
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#include "gtest/gtest.h"
#include "RingBuffer.h"
#include <limits.h>

class RingBufferTest : public testing::Test
{
protected:
	virtual void SetUp()
	{
		mRingBuffer = new RingBuffer<long, 6>();
		mCursor = new Cursor();
	}

	virtual void TearDown()
	{
		delete mRingBuffer;
		delete mCursor;
	}

	RingBuffer<long, 6> * mRingBuffer;
	Cursor * mCursor;
};

TEST_F( RingBufferTest, getHandlerIDTest )
{
	long eventHandlerID = mRingBuffer->getEventHandlerID(mCursor);
	EXPECT_EQ(1, eventHandlerID);
}

TEST_F( RingBufferTest, nextTest )
{
	static const long TEST_COUNT = 1024;
	bool test_success = true;

	for( long count = 0; count < TEST_COUNT; count++ )
	{
		if( count % 64 != mRingBuffer->next() )
			test_success = false;
	}

	EXPECT_TRUE(test_success);
}

TEST_F( RingBufferTest, isAvailableTest )
{
	static const long TEST_COUNT = 1024;
	long eventHandlerID = mRingBuffer->getEventHandlerID(mCursor);

	unsigned long publisher_seq;
	unsigned long eventHandler_seq;

	for( long count = 0; count < TEST_COUNT; count++ )
	{
		// Check available (publisher)
		publisher_seq = mRingBuffer->next();
		EXPECT_TRUE( mRingBuffer->isAvailable( publisher_seq ) );

		// Check available (eventHandler)
		eventHandler_seq = mRingBuffer->next(mCursor);
		EXPECT_FALSE( mRingBuffer->isAvailable( publisher_seq, eventHandlerID ) );
	}
}

TEST_F( RingBufferTest, releaseTest )
{
	static const long TEST_COUNT = 1024;
	long eventHandlerID = mRingBuffer->getEventHandlerID(mCursor);

	unsigned long publisher_seq;
	unsigned long eventHandler_seq;

	for( long count = 0; count < TEST_COUNT; count++ )
	{
		// Check available (publisher)
		publisher_seq = mRingBuffer->next();
		EXPECT_TRUE( mRingBuffer->isAvailable( publisher_seq ) );

		// Check available (eventHandler)
		eventHandler_seq = mRingBuffer->next(mCursor);
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_seq, eventHandlerID ) );

		// release (publisher)
		mRingBuffer->release( publisher_seq );
		EXPECT_FALSE( mRingBuffer->isAvailable( publisher_seq ) );
		EXPECT_TRUE( mRingBuffer->isAvailable( eventHandler_seq, eventHandlerID ) );

		// release (eventHandler)
		mRingBuffer->release( eventHandler_seq, eventHandlerID );
		EXPECT_TRUE( mRingBuffer->isAvailable( publisher_seq ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_seq, eventHandlerID ) );
	}
}

TEST_F( RingBufferTest, releaseTest_cascadeEventHandler )
{
	static const long TEST_COUNT = 1024;

	Cursor cursor[2];
	Cursor * cursor_1 = &cursor[0];
	Cursor * cursor_2 = &cursor[1];

	long eventHandlerID_1 = mRingBuffer->getEventHandlerID(cursor_1);
	long eventHandlerID_2 = mRingBuffer->getEventHandlerID(cursor_2);

	unsigned long publisher_seq;
	unsigned long eventHandler_1_seq;
	unsigned long eventHandler_2_seq;

	for( long count = 0; count < TEST_COUNT; count++ )
	{
		// Check available (publisher)
		publisher_seq = mRingBuffer->next();
		EXPECT_TRUE( mRingBuffer->isAvailable( publisher_seq ) );

		// Check available (eventHandlers)
		eventHandler_1_seq = mRingBuffer->next(cursor_1);
		eventHandler_2_seq = mRingBuffer->next(cursor_2);
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_1_seq, eventHandlerID_1 ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_2_seq, eventHandlerID_2 ) );

		// release (publisher)
		mRingBuffer->release( publisher_seq );
		EXPECT_FALSE( mRingBuffer->isAvailable( publisher_seq ) );
		EXPECT_TRUE( mRingBuffer->isAvailable( eventHandler_1_seq, eventHandlerID_1 ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_2_seq, eventHandlerID_2 ) );

		// release (eventHandler 1)
		mRingBuffer->release( eventHandler_1_seq, eventHandlerID_1 );
		EXPECT_FALSE( mRingBuffer->isAvailable( publisher_seq ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_1_seq, eventHandlerID_1 ) );
		EXPECT_TRUE( mRingBuffer->isAvailable( eventHandler_2_seq, eventHandlerID_2 ) );

		// release (eventHandler 2)
		mRingBuffer->release( eventHandler_2_seq, eventHandlerID_2 );
		EXPECT_TRUE( mRingBuffer->isAvailable( publisher_seq ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_1_seq, eventHandlerID_1 ) );
		EXPECT_FALSE( mRingBuffer->isAvailable( eventHandler_2_seq, eventHandlerID_2 ) );
	}
}

