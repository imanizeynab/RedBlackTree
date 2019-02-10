#pragma once

#include "InternalBinaryTreeNode.h"
#include <windows.h>

using namespace std;

template <class T, class IBTN>
class RedBlackTree : public BinaryTree<T,IBTN> {

public:
	virtual BinaryTreeNode	getRootNode() override { return BinaryTreeNode(mInorderEnd->mLeftChild); }

	virtual void  insert(T data) override {
		if (mInorderEnd->mLeftChild == 0) {
			insertRootNode(data);
		}
		else {
			IBTN* par = mInorderEnd->mLeftChild;
			while (1) {
				if (par->mData > data) {
					if (par->mLeftChild == 0) {
						insertLeftChild(BinaryTreeNode(par), data);
						break;
					}
					else {
						par = par->mLeftChild;
					}
				}
				else {
					if (par->mRightChild == 0) {
						insertRightChild(BinaryTreeNode(par), data);
						break;
					}
					else {
						par = par->mRightChild;
					}
				}
			}
		}
	}

	void setTextColor(int textColor, int backColor = 0)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		int colorAttribute = backColor << 4 | textColor;
		SetConsoleTextAttribute(consoleHandle, colorAttribute);
	}

	// This function is solely written to work on small binary trees.
	// The code has many other known limitations.
	void drawRedBlack(std::ostream& out) {
		if (mSize == 0)
			return;

		int maxDepth = 9;
		int depth = depthCalc(getRootNode().mActualNode, 1);
		depth = depth * 2 - 1;


		if (depth > maxDepth) {
			out << "Can't draw, the height of the tree is greater than " << (maxDepth + 1) / 2 << "\n";
			return;
		}

		char **map = new char *[depth];
		for (int i = 0; i < depth; i++) {
			map[i] = new char[80];
			for (int j = 0; j < 80; j++)
				map[i][j] = ' ';
		}

		recursiveDrawRedBlack(getRootNode().mActualNode, map, 40, 0);

		for (int i = 0; i < depth; i++)
			for (int j = 0; j < 80; j++) {
				if (map[i][j] == '.') {
					setTextColor(4, 0);
					map[i][j] = ' ';
					out << map[i][j];
					out << map[i][j + 1];
					out << map[i][j + 2];
					out << map[i][j + 3];
					j += 3;
				}
				else {
					out << map[i][j];
				}
				setTextColor(8, 0);
			}
		out << endl;
		for (int i = 0; i < depth; i++)
			delete[] map[i];
		delete[] map;
	}

protected:
	// E is parent and S is it's rightChild
	void LeftRotate(IBTN* E, IBTN* S) {
		if (E->mParent->mLeftChild == E) {
			E->mParent->mLeftChild = S;
		}
		else {
			E->mParent->mRightChild = S;
		}
		S->mParent = E->mParent;
		E->mParent = S;
		if (S->mLeftChild != 0) {
			S->mLeftChild->mParent = E;
		}
		E->mRightChild = S->mLeftChild;
		S->mLeftChild = E;

		S->mColor = 1;
		E->mColor = 0;
	}

	// S is parent and E is it's leftChild
	void RightRotate(IBTN* S, IBTN* E) {
		if (S->mParent->mLeftChild == S) {
			S->mParent->mLeftChild = E;
		}
		else {
			S->mParent->mRightChild = E;
		}
		E->mParent = S->mParent;
		S->mParent = E;
		if (E->mRightChild != 0) {
			E->mRightChild->mParent = S;
		}
		S->mLeftChild = E->mRightChild;
		E->mRightChild = S;

		E->mColor = 1;
		S->mColor = 0;
	}

	void FlipColor(IBTN* E, IBTN* S) {
		E->mColor = 1;
		S->mColor = 1;
		if(E->mParent->mParent != mInorderEnd)
			E->mParent->mColor = 0;
	}

	IBTN* check(IBTN* insertedNode, int& color) {
		IBTN* temp = 0;
		// both childern are red
		if (insertedNode->mParent->mLeftChild != 0 && insertedNode->mParent->mRightChild != 0) {
			if (insertedNode->mParent->mLeftChild->mColor == 0 && insertedNode->mParent->mRightChild->mColor == 0) {
				FlipColor(insertedNode->mParent->mLeftChild, insertedNode->mParent->mRightChild);
				temp = insertedNode->mParent;
				color = temp->mColor;
				return temp;
			}
			else {
				color = 1;
			}
		}
		// rightchild is red
		if (insertedNode->mColor == 0 && insertedNode->mParent->mRightChild == insertedNode) {
			LeftRotate(insertedNode->mParent, insertedNode);
			temp = insertedNode->mLeftChild;
			color = temp->mColor;
		}
		// left child and left grandchild are red
		else if (insertedNode->mColor == 0 && insertedNode->mParent->mColor == 0 && insertedNode->mParent->mLeftChild == insertedNode) {
			RightRotate(insertedNode->mParent->mParent, insertedNode->mParent);
			temp = insertedNode->mParent->mRightChild;
			color = temp->mColor;
		}
		else {
			color = 1;
		}
		return temp;
	}


	void recursiveDrawRedBlack(IBTN* root, char** lines, int x, int y) {
		int des = 1;
		for (int i = 0; i < y / 2 + 2; i++)
			des *= 2;
		des = 80 / des;
		//root:
		for (int i = 0; i < mNodeDisplayWidth; i++) {
			lines[y][x + i - mNodeDisplayWidth / 2] = (root->mData)[0];
			lines[y][x + i - mNodeDisplayWidth / 2 + 1] = (root->mData)[1];
			lines[y][x + i - mNodeDisplayWidth / 2 + 2] = (root->mData)[2];
			if (root->mColor == 0) {
				lines[y][x + i - mNodeDisplayWidth / 2 - 1] = '.';
			}
		}
		//left child:
		if (root->mLeftChild) {
			for (int i = 0; i < des; i++)
				lines[y + 1][x - i] = '-';
			lines[y + 1][x] = '|';
			recursiveDrawRedBlack(root->mLeftChild, lines, x - des, y + 2);
		}
		//right child:
		if (root->mRightChild) {
			for (int i = 0; i < des; i++)
				lines[y + 1][x + i] = '-';
			lines[y + 1][x] = '|';
			recursiveDrawRedBlack(root->mRightChild, lines, x + des, y + 2);
		}
	}

private:
	virtual void insertRootNode(T data) override {
		if (mInorderEnd->mLeftChild != 0)
			throw ("Error: Root already exists.");
		IBTN* root = new IBTN();
		root->mData = data;
		root->mParent = mInorderEnd;
		root->mLeftChild = 0;
		root->mRightChild = 0;
		mInorderEnd->mLeftChild = root;
		mSize = 1;
	}

	virtual void  insertLeftChild(const BinaryTreeNode& parentNode, T data) override {
		if (parentNode.hasLeftChild()) {
			throw ("Error: LeftChild already exists.");
		}
		IBTN* leftCh = new IBTN();
		leftCh->mData = data;
		leftCh->mParent = parentNode.mActualNode;
		leftCh->mColor = 0;
		leftCh->mLeftChild = 0;
		leftCh->mRightChild = 0;
		parentNode.mActualNode->mLeftChild = leftCh;
		mSize++;

		int color = 0;
		IBTN* shouldBeChecked = leftCh;
		while (color == 0) {
			shouldBeChecked = check(shouldBeChecked, color);
		}
	}

	// error if a right child already exists.
	virtual void insertRightChild(const BinaryTreeNode& parentNode, T data) override {
		if (parentNode.hasRightChild()) {
			throw ("Error: LeftChild already exists.");
		}
		IBTN* rightCh = new IBTN();
		rightCh->mData = data;
		rightCh->mParent = parentNode.mActualNode;
		rightCh->mColor = 0;
		rightCh->mLeftChild = 0;
		rightCh->mRightChild = 0;
		parentNode.mActualNode->mRightChild = rightCh;
		mSize++;

		int color = 0;
		IBTN* shouldBeChecked = rightCh;
		while (color == 0) {
			shouldBeChecked = check(shouldBeChecked, color);
		}
	}

};



