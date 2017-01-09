//
//  main.cpp
//  HW_C3
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "LCS.h"
#include <iostream>

int main(int argc, const char * argv[])
{
	std::string s1 = "ABCBDAB";
	std::string s2 = "BDCABA";

	// --------------------------------
	//	HW.C3.1
	// --------------------------------
	std::cout << LCS_recursion( s1.c_str(), s2.c_str(), (int)s1.length(), (int)s2.length() ) << std::endl;

	// --------------------------------
	//	HW.C3.2
	// --------------------------------
	std::cout << LCS_memoization( s1.c_str(), s2.c_str(), (int)s1.length(), (int)s2.length() ) << std::endl;

	// --------------------------------
	//	HW.C3.3
	// --------------------------------
	std::cout << LCS_bottom_up( s1.c_str(), s2.c_str(), (int)s1.length(), (int)s2.length() ) << std::endl;
	
	// --------------------------------
	//	HW.C3.4
	// --------------------------------
	auto substr = LCS_result( s1.c_str(), s2.c_str(), (int)s1.length(), (int)s2.length() );
	for( int i = 0; i < substr.size(); ++i )
	{
		std::cout << substr[i] << std::endl;
		delete[] substr[i];
	}

	// --------------------------------
	//	HW.C3.5
	// --------------------------------
	// TODO

    return 0;
}

