/**
 * @file	main.cpp
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#include "MockServer.h"
#include "Platform.h"

#include <iostream>
#include <iomanip>

const long nSec = 1000000000;

const int newClientPerSec = 100;
const int logoutRate = 5;
const int testTime = 5;

int main(int argc, char *argv[])
{
	// TODO : connect to server
	long startTime = monoTime();
	long shutdownTime = startTime + testTime * nSec;
	long lastLogTime = startTime;
	long currentTime;

	MockServer mockServer( nSec / newClientPerSec );

	// Main loop
	long expectedLogoutCount = 0;
	while( ( currentTime = monoTime() ) < shutdownTime )
	{
		mockServer.process( currentTime );

		if( currentTime - lastLogTime > nSec )
		{
			lastLogTime += nSec;
			std::cout
				<< "Client(" << mockServer.clientCount() << ')'
				<< "Logout(" << mockServer.logoutCount() << ')'
				<< "Idle(" << mockServer.idleCount() << ')'
				<< "Move(" << mockServer.moveCount() << ')'
				<< "Chat(" << mockServer.chatCount() << ')'
				<< "Trade(" << mockServer.tradeCount() << ')'
				<< std::endl;
			expectedLogoutCount += ( mockServer.clientCount() * logoutRate ) / 100;
			mockServer.expectLogoutCount( expectedLogoutCount );
		}
	}

	return 0;
}

