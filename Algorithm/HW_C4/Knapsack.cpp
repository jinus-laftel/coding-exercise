//
//  Knapsack.cpp
//  HW_C4
//
//  Created by JinWoo Lee on 2014. 8. 25..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "Knapsack.h"

#include <functional>
#include <stdlib.h>

int Knapsack_01_recursive( Item item[], int len, int capacity )
{
	std::function<int(int, int)> recur_func = [&]( int idx, int remain )
	{
		if ( idx >= len )
			return 0;

		int selected = ( item[idx].weight > remain ) ? 0 : recur_func( idx + 1, remain - item[idx].weight ) + item[idx].value;
		int unselected = recur_func( idx + 1, remain );

		return ( selected > unselected ) ? selected : unselected;
	};

	return recur_func( 0, capacity );
}

float Knapsack_frac_iter_greedy( Item item[], int len, int capacity )
{
	// --------------------------------
	//	Sort by value per weight
	// --------------------------------
	qsort( item, len, sizeof( Item ), []( const void * left, const void * right )
	{
		Item * l = (Item *)left;
		Item * r = (Item *)right;
		if ( l->value * r->weight > r->value * l->weight )	// ( l->value / l->weight > r->value / r->weight )
			return -1;
		else if ( l->value * r->weight < r->value * l->weight )	// ( l->value / l->weight < r->value / r->weight )
			return 1;
		else
			return 0;
	});
	
	// --------------------------------
	//	Calculate value
	// --------------------------------
	float value = 0;
	
	for ( int i = 0; i < len; ++i )
	{
		if ( capacity <= 0 )
			break;
		
		if ( capacity > item[i].weight )
		{
			value += item[i].value;
			capacity -= item[i].weight;
		}
		else
		{
			value += ( float )(item[i].value * capacity) / item[i].weight;
			capacity = 0;
		}
	}

	return value;
}

int Knapsack_01_dynamic( Item item[], int len, int capacity )
{
	// --------------------------------
	//	Init memo
	// --------------------------------
	int * max_value = new int[capacity + 1];
	bool ** selected = new bool*[capacity + 1];

	for ( int i = 0; i <= capacity; ++i )
	{
		selected[i] = new bool[len];

		for ( int j = 0; j < len; ++j )
			selected[i][j] = false;
	}

	// --------------------------------
	//	Calc max value
	// --------------------------------
	max_value[0] = 0;
	
	for ( int weight = 1; weight <= capacity; ++weight )
	{
		int sub_max = 0;
		int sel_idx = 0;
		for ( int i = 0; i < len; ++i )
		{
			if ( item[i].weight > weight )
				continue;
			
			if ( selected[ weight - item[i].weight ][i] )
				continue;
			
			int value = item[i].value + max_value[ weight - item[i].weight ];

			if ( value > sub_max )
			{
				sub_max = value;
				sel_idx = i;
			}
		}
		max_value[weight] = sub_max;
		
		if ( sub_max > 0 )
		{
			selected[weight][sel_idx] = true;

			for ( int i = 0; i < len; ++i )
				selected[weight][i] |= selected[ weight - item[sel_idx].weight ][i];
		}
	}
	
	int result = max_value[capacity];

	// --------------------------------
	//	Cleanup
	// --------------------------------
	for ( int i = 0; i < capacity; ++i )
		delete selected[i];

	delete selected;
	delete max_value;

	return result;
}
