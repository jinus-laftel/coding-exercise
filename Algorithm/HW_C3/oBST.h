//
//  oBST.h
//  HW_C3
//
//  Created by JinWoo Lee on 2014. 8. 14..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

#include <ostream>

template<typename KEY_TYPE>
class BST
{
private:
	struct Node
	{
		KEY_TYPE key;
		Node * left;
		Node * right;
	};

public:
	template<typename P>
	void MakeOptimalBST_recursive( KEY_TYPE * key, P * probability, int length )
	{
		//
	}

	template<typename P>
	void MakeOptimalBST_memoization( KEY_TYPE * key, P * probability, int length )
	{
		//
	}

	template<typename P>
	void MakeOptimalBST_bottom_up( KEY_TYPE * key, P * probability, int length )
	{
		//
	}
	
	std::string toString()
	{
		//
	}

private:
	Node * m_Root;
};

template<typename KEY_TYPE>
std::ostream & operator<<( std::ostream & stream, const BST<KEY_TYPE> & tree )
{
	return stream << tree.toString();
}
