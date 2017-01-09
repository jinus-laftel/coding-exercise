//
//  main.cpp
//  HW_C2
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "MatrixChain.h"
#include <iostream>

int main(int argc, const char * argv[])
{
	int array[] = { 4, 3, 5, 2, 8, 9, 3, 6 };
	
	std::cout
		<< matrixChain_recursion( array, 1, 7 ) << ", "
		<< matrixChain_memoization( array, 1, 7 ) << ", "
		<< matrixChain_bottom_up( array, 1, 7 ) << std::endl;

	int * positionMatrix[7 + 1];
	for ( int i = 0; i <= 7; ++i )
		positionMatrix[i] = new int[7 + 1];
	
	matrixChain_position( array, 1, 7, positionMatrix );
	matrixChain_print( positionMatrix, 1, 7 );
	std::cout << std::endl;

	for ( int i = 0; i <= 7; ++i )
		delete [] positionMatrix[i];

    return 0;
}
