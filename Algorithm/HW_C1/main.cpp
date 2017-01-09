//
//	main.cpp
//	HW_C1
//
//	Created by JinWoo Lee on 2014. 7. 22.
//	Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "BinaryTree.h"
#include "Fibonacci.h"
#include "RodCutting.h"

#include <iostream>

//void MakeTestData( BinaryTree & bt )
//{
//	BinaryTreeNode * root = new BinaryTreeNode( 1 );
//	BinaryTreeNode * newNode;
//	
//	newNode = new BinaryTreeNode( 2 );
//	root->SetLeft( newNode );
//	
//	newNode = new BinaryTreeNode( 3 );
//	root->SetRight( newNode );
//	
//	newNode = new BinaryTreeNode( 4 );
//	root->GetLeft()->SetLeft( newNode );
//	
//	newNode = new BinaryTreeNode( 5 );
//	root->GetLeft()->SetRight( newNode );
//	
//	newNode = new BinaryTreeNode( 6 );
//	root->GetRight()->SetLeft( newNode );
//	
//	newNode = new BinaryTreeNode( 7 );
//	root->GetRight()->SetRight( newNode );
//	
//	bt.SetRoot( root );
//}


int main(int argc, const char * argv[])
{
//	BinaryTree bt;
//	
//	MakeTestData( bt );
//	std::cout << bt << std::endl;
//
//	// Test HW.C1.1
//	std::cout << bt.CountNodes() << " Nodes" << std::endl;
//	// Test HW.C1.2
//	std::cout << bt.BFS() << std::endl;
//
//	// Test HW.C1.3
//	for ( int i = 0; i < 10; ++i )
//	{
//		std::cout << "Fibonacci " << i << " : "
//			<< fibonacci_by_recursion( i )
//			<< ", " << fibonacci_top_down( i )
//			<< ", " << fibonacci_bottom_up( i )
//			<< std::endl;
//	}

	// Rod Price
	int rod_price[30] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30, };
	int piece[30];

	for	( int i = 0; i < 20; ++i )
	{
		std::cout << "Rod(" << i << ") "
			// Test HW.C1.4
			<< "Cutting Price : " << rod_cutting_combination( rod_price, i )
			// Test HW.C1.5
			<< ", " << rod_cutting_first_cut( rod_price, i )
			// Test HW.C1.6
			<< ", " << rod_cutting_top_down( rod_price, i )
			// Test HW.C1.7
			<< ", " << rod_cutting_bottom_up( rod_price, i ) << " (";

		// Test HW.C1.8
		rod_cutting_pieces( rod_price, i, piece );
		int piece_len = i;
		while ( piece_len > 0 )
		{
			std::cout << piece[piece_len];
			piece_len -= piece[piece_len];
			if ( piece_len > 0 )
				std::cout << ", ";
		}
		std::cout << ")" << std::endl;
	}

	return 0;
}
