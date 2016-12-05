//
//  Knapsack.h
//  HW_C4
//
//  Created by JinWoo Lee on 2014. 8. 25..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

struct Item
{
	int weight;
	int value;
};

int Knapsack_01_recursive( Item item[], int len, int capacity );
float Knapsack_frac_iter_greedy( Item item[], int len, int capacity );
int Knapsack_01_dynamic( Item item[], int len, int capacity );
