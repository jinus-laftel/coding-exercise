//
//  MatrixChain.h
//  HW_C2
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

#define ROW(arr,i) (arr[(i)-1])
#define COL(arr,i) (arr[(i)])

int matrixChain_recursion( int * arr, int left, int right );
int matrixChain_memoization( int * arr, int left, int right );
int matrixChain_bottom_up( int * arr, int left, int right );

int matrixChain_position( int * arr, int left, int right, int ** positionMatrix );
void matrixChain_print( int ** positionMatrix, int left, int right );
