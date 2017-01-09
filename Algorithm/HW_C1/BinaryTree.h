//
//  BinaryTree.h
//  HW_C1
//
//  Created by JinWoo Lee on 2014. 7. 22.
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#pragma once

#include <string>

/**
 *	Node of Binary Tree
 */
class BinaryTreeNode
{
public:
	BinaryTreeNode( int data ) : m_Data(data), m_Left(nullptr), m_Right(nullptr) {}
	~BinaryTreeNode() { delete m_Left; delete m_Right; }

	// Set, Get
	void SetData( int data ) { m_Data = data; }
	void SetLeft( BinaryTreeNode * node ) { m_Left = node; }
	void SetRight( BinaryTreeNode * node ) { m_Right = node; }
	int GetData() const { return m_Data; }
	BinaryTreeNode * GetLeft() const { return m_Left; }
	BinaryTreeNode * GetRight() const { return m_Right; }

	int CountNodes() const;
	
private:
	int					m_Data;
	BinaryTreeNode *	m_Left;
	BinaryTreeNode *	m_Right;
};

std::ostream & operator<<( std::ostream & stream, const BinaryTreeNode * node );

/**
 *	Binary tree
 */
class BinaryTree
{
public:
	BinaryTree() : m_Root(nullptr) {}
	~BinaryTree() { delete m_Root; }

	// Set, Get
	void SetRoot( BinaryTreeNode * node ) { m_Root = node; }
	BinaryTreeNode * GetRoot() const { return m_Root; }
	
	int CountNodes() const { return m_Root->CountNodes(); }
	std::string BFS() const;

private:
	BinaryTreeNode * m_Root;
};

std::ostream & operator<<( std::ostream & stream, const BinaryTree & tree );
