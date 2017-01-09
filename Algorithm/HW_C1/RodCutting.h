//
//  RodCutting.h
//  HW_C1
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

int rod_cutting_combination( int * price, int length );
int rod_cutting_first_cut( int * price, int length );
int rod_cutting_top_down( int * price, int length );
int rod_cutting_bottom_up( int * price, int length );
int rod_cutting_pieces( int * price, int length, int * piece );
