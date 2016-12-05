//
//  ActSel.h
//  HW_C4
//
//  Created by JinWoo Lee on 2014. 8. 21..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma	once

struct Act
{
	int start;
	int end;
};

int ActSel_recursive( Act act[], int len );
int ActSel_recur_greedy( Act act[], int len );
int ActSel_iter_greedy( Act act[], int len );
