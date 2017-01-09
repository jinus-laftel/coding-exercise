//
//  MatrixChain.cpp
//  HW_C2
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "MatrixChain.h"
#include <iostream>

int matrixChain_memoization_recursion( int * arr, int left, int right, int ** matrixChain );


int matrixChain_recursion( int * arr, int left, int right )
{
	if ( left == right )
		return 0;

	int min = ROW(arr, left) * COL(arr, left) * COL(arr, right) + matrixChain_recursion( arr, left + 1, right );
	
	for ( int i = left + 1; i < right; ++i )
	{
		int count = ROW(arr, left) * COL(arr, i) * COL(arr, right)
			+ matrixChain_recursion( arr, left, i ) + matrixChain_recursion( arr, i+1, right );

		if ( count < min )
			min = count;
	}
	return min;
}


int matrixChain_memoization( int * arr, int left, int right )
{
	int * matrixChain[left + 1];
	
	for ( int i = 0; i <= left; ++i )
	{
		matrixChain[i] = new int[right + 1];
		
		for ( int j = 0; j <= right; ++j )
			matrixChain[i][j] = -1;
	}
	
	int result = matrixChain_memoization_recursion( arr, left, right, matrixChain );
	
	for ( int i = 0; i <= left; ++i )
		delete [] matrixChain[i];

	return result;
}


int matrixChain_memoization_recursion( int * arr, int left, int right, int ** matrixChain )
{
	if ( matrixChain[left][right] < 0 )
	{
		if ( left == right )
		{
			matrixChain[left][right] = 0;
			return 0;
		}
	
		int min = ROW(arr, left) * COL(arr, left) * COL(arr, right) + matrixChain_recursion( arr, left + 1, right );
	
		for ( int i = left + 1; i < right; ++i )
		{
			int count = ROW(arr, left) * COL(arr, i) * COL(arr, right)
				+ matrixChain_recursion( arr, left, i ) + matrixChain_recursion( arr, i+1, right );
		
			if ( count < min )
				min = count;
		}
	
		matrixChain[left][right] = min;
	}

	return matrixChain[left][right];
}


int matrixChain_bottom_up( int * arr, int left, int right )
{
	int matrixChain[right + 1][right + 1];

	for ( int i = left; i <= right; ++i )
		matrixChain[i][i] = 0;

	for ( int level = 1; level <= right - left; ++level )
	{
		int l = left;
		int r = left + level;

		while ( r <= right )
		{
			int min = ROW(arr, l) * COL(arr, l) * COL(arr, r) + matrixChain[l + 1][r];
			
			for ( int i = l + 1; i < r; ++i )
			{
				int count = ROW(arr, l) * COL(arr, i) * COL(arr, r)
					+ matrixChain[l][i] + matrixChain[i + 1][r];
				
				if ( count < min )
					min = count;
			}
			
			matrixChain[l][r] = min;
			l++;
			r++;
		}
	}
	
	return matrixChain[left][right];
}

int matrixChain_position( int * arr, int left, int right, int ** positionMatrix )
{
	int matrixChain[right + 1][right + 1];

	for ( int i = left; i <= right; ++i )
		matrixChain[i][i] = 0;
	
	for ( int level = 1; level <= right - left; ++level )
	{
		int l = left;
		int r = left + level;
		
		while ( r <= right )
		{
			int min = ROW(arr, l) * COL(arr, l) * COL(arr, r) + matrixChain[l + 1][r];
			int position = l;
			
			for ( int i = l + 1; i < r; ++i )
			{
				int count = ROW(arr, l) * COL(arr, i) * COL(arr, r)
					+ matrixChain[l][i] + matrixChain[i + 1][r];
				
				if ( count < min )
				{
					min = count;
					position = i;
				}
			}

			matrixChain[l][r] = min;
			positionMatrix[l][r] = position;
			l++;
			r++;
		}
	}
	
	return matrixChain[left][right];
}

void matrixChain_print( int ** positionMatrix, int left, int right )
{
	if ( left == right )
	{
		std::cout << "A" << left;
		return;
	}
	
	std::cout << "(";
	matrixChain_print( positionMatrix, left, positionMatrix[left][right] );
	matrixChain_print( positionMatrix, positionMatrix[left][right] + 1, right );
	std::cout << ")";
}
