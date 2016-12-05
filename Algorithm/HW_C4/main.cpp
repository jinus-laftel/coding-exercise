//
//  main.cpp
//  HW_C4
//
//  Created by JinWoo Lee on 2014. 8. 21..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "ActSel.h"
#include "Knapsack.h"

#include <iostream>

int main(int argc, const char * argv[])
{
	// --------------------------------
	//	HW.C4.1 ~ HW.C4.3
	// --------------------------------
	Act act[] = {
		{ 1, 4 }, { 3, 5 }, { 0, 6 }, { 5, 7 }, { 3, 9 },
		{ 5, 9 }, { 6, 10 }, { 8, 11 }, { 8, 12 }, { 2, 14 },
		{ 12, 16 }
	};
	
	std::cout << "Max Activity : "
		<< ActSel_recursive( act, 11 ) << ", "
		<< ActSel_recur_greedy( act, 11 ) << ", "
		<< ActSel_iter_greedy( act, 11 ) << std::endl;

	// --------------------------------
	//	HW.C4.4 ~ HW.C4.6
	// --------------------------------
	Item item[] = {
		{ 10, 60 }, { 20, 100 }, { 30, 120 }
	};
	
	std::cout << "Knapsack Max Value : "
		<< "(0/1)" << Knapsack_01_recursive( item, 3, 50 ) << ", "
		<< "(frag)" << Knapsack_frac_iter_greedy( item, 3, 50 ) << ", "
		<< "(0/1)" << Knapsack_01_dynamic( item, 3, 50 ) << std::endl;
	
    return 0;
}

