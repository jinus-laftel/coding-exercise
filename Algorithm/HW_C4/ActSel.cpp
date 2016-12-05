//
//  ActSel.cpp
//  HW_C4
//
//  Created by JinWoo Lee on 2014. 8. 21..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "ActSel.h"
#include <functional>

int ActSel_recursive( Act act[], int len )
{
	std::function<int(int, int, int, int)> recur_func = [&]( int sIdx, int eIdx, int sTime, int eTime )
	{
		int max = 0;
		
		if ( sIdx > eIdx || sTime > eTime )
			return 0;
		
		for ( int i = sIdx; i <= eIdx; ++i )
		{
			if ( act[i].start >= sTime && act[i].end <= eTime )
			{
				int count = 1
					+ recur_func( sIdx, i - 1, sTime, act[i].start )
					+ recur_func( i + 1, eIdx, act[i].end, eTime );
				if ( count > max )
					max = count;
			}
		}
		
		return max;
	};

	return recur_func( 0, len - 1, 0, act[len - 1].end );
}

int ActSel_recur_greedy( Act act[], int len )
{
	std::function<int(int, int)> recur_func = [&]( int idx, int end )
	{
		if ( idx >= len )
			return 0;
		
		if ( act[idx].start >= end )
			return recur_func( idx + 1, act[idx].end ) + 1;
		
		return recur_func( idx + 1, end );

	};

	return recur_func( 0, 0 );
}

int ActSel_iter_greedy( Act act[], int len )
{
	int count = 0;
	int end = 0;

	for ( int i = 0; i < len; ++i )
	{
		if ( act[i].start >= end )
		{
			end = act[i].end;
			count++;
		}
	}
	
	return count;
}
