// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2018 (1397 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi

#pragma once

template <class T, class IBTN>
class BinaryTree;
template <class T, class IBTN>
class RedBlackTree;

template <class T>
class InternalBinaryTreeNode
{
public:

	InternalBinaryTreeNode(void)
	{
		mLeftChild = 0;
		mRightChild = 0;
	}

	virtual ~InternalBinaryTreeNode(void)
	{
	}

	virtual void	setData(const T& data)
	{
		mData = data;
	}

	virtual T	getData()
	{
		return mData;
	}

	virtual InternalBinaryTreeNode<T>*	getLeftChild()
	{
		return mLeftChild;
	}

	virtual InternalBinaryTreeNode<T>*	getRightChild()
	{
		return mRightChild;
	}


	friend class BinaryTree<T, InternalBinaryTreeNode<T>>;
	friend class RedBlackTree<T, InternalBinaryTreeNode<T>>;

protected:
	T							mData;
	InternalBinaryTreeNode<T>*	mParent;
	InternalBinaryTreeNode<T>*	mLeftChild;
	InternalBinaryTreeNode<T>*	mRightChild;
	int							mColor = 1; // 1 means Black and 0 means Red          
	// used for drawing
	int							mPosition; // Position in the level of tree
};
