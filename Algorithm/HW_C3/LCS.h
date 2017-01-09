//
//  LCS.h
//  HW_C3
//
//  Created by JinWoo Lee on 2014. 8. 13..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

#include <functional>
#include <vector>

template<typename T>
int LCS_recursion( const T * seq1, const T * seq2, int len1, int len2 )
{
	std::function<int(int, int)> recur_func = [&]( int len1, int len2 )
	{
		int longest = 0;

		if ( len1 > 0 && len2 > 0 )
		{
			auto lcs1 = recur_func( len1 - 1, len2 - 1 );
			auto lcs2 = recur_func( len1, len2 - 1 );
			auto lcs3 = recur_func( len1 - 1, len2 );
			
			if ( lcs1 >= lcs2 && lcs1 >= lcs3 )
				longest = ( seq1[ len1 - 1 ] == seq2[ len2 - 1 ] ) ? lcs1 + 1 : lcs1;
			else
				longest = ( lcs2 > lcs3 ) ? lcs2 : lcs3;
		}

		return longest;
	};
	
	return recur_func( len1, len2 );
}

template<typename T>
int LCS_memoization( const T * seq1, const T * seq2, int len1, int len2 )
{
	// --------------------------------
	//	Initialization
	// --------------------------------
	int ** memory = new int*[len1 + 1];
	
	for ( int i = 0; i <= len1; ++i )
	{
		memory[i] = new int[len2 + 1];
		
		for ( int j = 0; j <= len2; ++j )
			memory[i][j] = -1;
	}
	
	// --------------------------------
	//	Run
	// --------------------------------
	std::function<int(int, int)> recur_func = [&]( int len1, int len2 )
	{
		if ( memory[len1][len2] >= 0 )
			return memory[len1][len2];
		
		int longest = 0;
		
		if ( len1 > 0 && len2 > 0 )
		{
			auto lcs1 = recur_func( len1 - 1, len2 - 1 );
			auto lcs2 = recur_func( len1, len2 - 1 );
			auto lcs3 = recur_func( len1 - 1, len2 );
			
			if ( lcs1 >= lcs2 && lcs1 >= lcs3 )
				longest = ( seq1[ len1 - 1 ] == seq2[ len2 - 1 ] ) ? lcs1 + 1 : lcs1;
			else
				longest = ( lcs2 > lcs3 ) ? lcs2 : lcs3;
		}
		
		memory[len1][len2] = longest;

		return longest;
	};

	int result = recur_func( len1, len2 );
	
	// --------------------------------
	//	Finalization
	// --------------------------------
	for ( int i = 0; i <= len1; ++i )
		delete [] memory[i];
	
	delete [] memory;

	return result;
}

template<typename T>
int LCS_bottom_up( const T * seq1, const T * seq2, int len1, int len2 )
{
	// --------------------------------
	//	Initialization
	// --------------------------------
	int ** memory = new int*[len1 + 1];
	
	for ( int i = 0; i <= len1; ++i )
	{
		memory[i] = new int[len2 + 1];
		
		for ( int j = 0; j <= len2; ++j )
			memory[i][j] = 0;
	}
	
	// --------------------------------
	//	Run
	// --------------------------------
	for ( int i = 1; i <= len1; ++i )
	{
		for ( int j = 1; j <= len2; ++j )
		{
			auto lcs1 = memory[i-1][j-1];
			auto lcs2 = memory[i][j-1];
			auto lcs3 = memory[i-1][j];
			
			if ( lcs1 >= lcs2 && lcs1 >= lcs3 )
				memory[i][j] = ( seq1[i-1] == seq2[j-1] ) ? lcs1 + 1 : lcs1;
			else
				memory[i][j] = ( lcs2 > lcs3 ) ? lcs2 : lcs3;
		}
	}
	
	int result = memory[len1][len2];
	
	// --------------------------------
	//	Finalization
	// --------------------------------

	for ( int i = 0; i <= len1; ++i )
		delete [] memory[i];
	
	delete [] memory;
	
	return result;
}

template<typename T>
std::vector<char *> LCS_result( const T * seq1, const T * seq2, int len1, int len2 )
{
	// --------------------------------
	//	Initialization
	// --------------------------------
	int ** memory = new int*[len1 + 1];
	
	for ( int i = 0; i <= len1; ++i )
	{
		memory[i] = new int[len2 + 1];
		
		for ( int j = 0; j <= len2; ++j )
			memory[i][j] = 0;
	}
	
	// --------------------------------
	//	Run
	// --------------------------------
	for ( int i = 1; i <= len1; ++i )
	{
		for ( int j = 1; j <= len2; ++j )
		{
			auto lcs1 = memory[i-1][j-1];
			auto lcs2 = memory[i][j-1];
			auto lcs3 = memory[i-1][j];
			
			if ( lcs1 >= lcs2 && lcs1 >= lcs3 )
				memory[i][j] = ( seq1[i-1] == seq2[j-1] ) ? lcs1 + 1 : lcs1;
			else
				memory[i][j] = ( lcs2 > lcs3 ) ? lcs2 : lcs3;
		}
	}
	
	int result = memory[len1][len2];
	
	// --------------------------------
	//	Subsequence
	// --------------------------------
	T * subseq = new T[result + 1];
	subseq[result] = '\0';
	std::vector<char *> subseq_vector;

	std::function<void(int, int, int)> recur_func = [&]( int len1, int len2, int length )
	{
		if ( length == 0 )
		{
			T * temp = new T[result + 1];
			std::memmove( temp, subseq, result + 1);
			subseq_vector.push_back( temp );
			return;
		}

		auto lcs0 = memory[len1][len2];
		auto lcs1 = memory[len1-1][len2];
		auto lcs2 = memory[len1][len2-1];
		
		if ( lcs0 <= lcs1 )
			recur_func( len1 - 1, len2, length );
		
		if ( lcs0 <= lcs2 )
			recur_func( len1, len2 - 1, length );
		
		if ( lcs0 > lcs1 && lcs0 > lcs2 )
		{
			subseq[length - 1] = seq1[len1 - 1];
			recur_func( len1 - 1, len2 - 1, length - 1 );
		}
		
	};
	
	recur_func( len1, len2, result );
	
	delete[] subseq;
	
	// --------------------------------
	//	Finalization
	// --------------------------------
	
	for ( int i = 0; i <= len1; ++i )
		delete [] memory[i];
	
	delete [] memory;
	
	return subseq_vector;
}
