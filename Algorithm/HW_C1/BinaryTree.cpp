//
//  BinaryTree.cpp
//  HW_C1
//
//  Created by JinWoo Lee on 2014. 7. 22.
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "BinaryTree.h"
#include <ostream>
#include <sstream>
#include <queue>

int BinaryTreeNode::CountNodes() const
{
	if ( this == nullptr )
		return 0;

	return m_Left->CountNodes() + m_Right->CountNodes() + 1;
}

std::ostream & operator<<( std::ostream & stream, const BinaryTreeNode * node )
{
	if ( ! node )
		return stream << ".";

	return stream
		<< "( " << node->GetLeft()
		<< " " << node->GetData()
		<< " " << node->GetRight()
		<< " )";
}

std::string BinaryTree::BFS() const
{
	std::stringstream strstream;
	std::queue<BinaryTreeNode *> queue;
	
	queue.push( m_Root );
	
	while ( ! queue.empty() )
	{
		BinaryTreeNode * node = queue.front();
		if ( node )
		{
			strstream << node->GetData() << " ";
			queue.push( node->GetLeft() );
			queue.push( node->GetRight() );
		}
		queue.pop();
	}
	
	return strstream.str();
}

std::ostream & operator<<( std::ostream & stream, const BinaryTree & tree )
{
	return stream << tree.GetRoot();
}
