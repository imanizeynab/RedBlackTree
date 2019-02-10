#include "../src/BinaryTree.h"
#include "../src/RedBlackTree.h"
#include "../src/Student.h"
#include <iostream>


using namespace std;
typedef RedBlackTree<Student, InternalBinaryTreeNode<Student>>  StudentRedBlack;

int main() {
	int input;
	bool result = false;
	StudentRedBlack*  rb = new StudentRedBlack;
	rb->setNodeDisplayWidth(1);
	for (int i = 1; i < 31; i++) {
		rb->insert(Student(i));
		rb->drawRedBlack(cout);
	}

	int dummy;
	cin >> dummy;

	return 0;
}
