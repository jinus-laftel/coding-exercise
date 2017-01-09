//
//  Fibonacci.cpp
//  HW_C1
//
//  Created by JinWoo Lee on 2014. 7. 22.
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "Fibonacci.h"
#include <stdexcept>


long fibonacci_by_recursion( int num )
{
	if ( num < 0 )
		throw new std::invalid_argument( "num must not be negative" );
	if ( num < 2 )
		return num;
	return fibonacci_by_recursion( num - 1 ) + fibonacci_by_recursion( num - 2 );
}


long fibonacci_top_down( int num, long * array )
{
	if ( ! array )
	{
		array = new long[num + 2];
		array[0] = 0;
		array[1] = 1;
		for ( int i = 2; i <= num; ++i )
			array[i] = -1;
	
		long result = fibonacci_top_down( num, array );
		delete[] array;

		return result;
	}

	if ( array[num] != -1 )
		return array[num];

	array[num] = fibonacci_top_down( num - 1, array ) + fibonacci_top_down( num - 2, array );

	return array[num];
}


long fibonacci_bottom_up( int num )
{
	long * array = new long[num + 1];
	
	array[0] = 0;
	array[1] = 1;
	for( int i = 2; i <= num; ++i )
	{
		array[i] = array[i - 1] + array[i - 2];
	}
	
	long result = array[num];
	delete [] array;

	return result;
}
