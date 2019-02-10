// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2018 (1397 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi

#pragma once

#include <stack>
#include "InternalBinaryTreeNode.h"

using namespace std;

//template <class T, class IBTN = InternalBinaryTreeNode<T>>
template <class T, class IBTN>
class BinaryTree {
public:

	class BinaryTreeNode {
	public:
		virtual ~BinaryTreeNode(void) {}
		virtual T&	getData() { return mActualNode->getData(); }
		virtual void	setData(const T& data) { return mActualNode->setData(data); }
		virtual bool	hasLeftChild() const { return mActualNode->getLeftChild() != 0; }
		virtual BinaryTreeNode	getLeftChild()const { return BinaryTreeNode(mActualNode->getLeftChild()); }
		virtual bool	hasRightChild() const { return mActualNode->getRightChild() != 0; }
		virtual BinaryTreeNode	getRightChild() const { return BinaryTreeNode(mActualNode->getRightChild()); }

	private:
		template <class T, class R>
		friend class BinaryTree;
		template <class T, class R>
		friend class RedBlackTree;
		BinaryTreeNode(IBTN* node) { mActualNode = node; }

		IBTN	*mActualNode;
	};

protected:

	IBTN * mRevInorderEnd;
	IBTN* mRevPostOrderEnd;
	IBTN* mInorderEnd;
	IBTN* mPreorderEnd;

	int		mNodeDisplayWidth;
	int		mSize;

public:
	BinaryTree(void) {
		mNodeDisplayWidth = 2;
		mSize = 0;
		mRevInorderEnd = new IBTN();
		mRevPostOrderEnd = new IBTN();
		mInorderEnd = new IBTN();
		mPreorderEnd = new IBTN();
		mRevInorderEnd->mLeftChild = mRevPostOrderEnd;
		mRevInorderEnd->mRightChild = mInorderEnd;
		mInorderEnd->mRightChild = mPreorderEnd;
	}

	// caution: don't interpret virtual destrucor as an ordinary virtual function!
	virtual ~BinaryTree(void) {
		DeleteSubtree(mRevInorderEnd);
	}

	int	size() { return mSize; }
	void DeleteSubtree(IBTN* node) {
		if (node->mLeftChild)
			DeleteSubtree(node->mLeftChild);
		if (node->mRightChild)
			DeleteSubtree(node->mRightChild);
		delete node;
	}

	bool	isEmpty() {
		return mInorderEnd->mLeftChild == 0;
	}

	virtual BinaryTreeNode	getRootNode() = 0;

	virtual BinaryTreeNode	getHeaderRootNode() {
		return BinaryTreeNode(mRevInorderEnd);
	}

	virtual void insert(T data) = 0;

	void setNodeDisplayWidth(int width) {
		mNodeDisplayWidth = width;
	}

protected:

	int depthCalc(IBTN* root, int depth) {
		int res = depth;
		if (root->mRightChild) {
			int rightDepth = depthCalc(root->mRightChild, depth + 1);
			res = (res > rightDepth) ? res : rightDepth;
		}
		if (root->mLeftChild) {
			int leftDepth = depthCalc(root->mLeftChild, depth + 1);
			res = (res > leftDepth) ? res : leftDepth;
		}
		return res;
	}

protected:
	virtual IBTN*	getActualNode(const BinaryTreeNode& node) { return node.mActualNode; }

private:
	virtual void	insertRootNode(T data) = 0;

	// error if a left child already exists.
	virtual void insertLeftChild(const BinaryTreeNode& parentNode, T data) = 0;

	// error if a right child already exists.
	virtual void insertRightChild(const BinaryTreeNode& parentNode, T data) = 0;
};

