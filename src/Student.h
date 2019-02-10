#pragma once

#include <stdio.h>
#include <stdlib.h>

using namespace std;
class Student{

public:
	Student(int number) {
		setId(number);
	}

	Student() {
	}

	int getId() {
		return id;
	}

	void setId(int number) {
		id = number;
	}

	string getName() {
		return name;
	}

	void setName(string esm) {
		name = esm;
	}

	bool operator==(Student stu)const {
		if (id == stu.getId())
			return true;
		else
			return false;
	}

	bool operator>(Student stu)const {
		if (id > stu.getId())
			return true;
		else
			return false;
	}
	bool operator<(Student stu)const {
		if (id < stu.getId())
			return true;
		else
			return false;
	}

	char operator[](int a)const {
		char c[5];
		itoa(id, c, 10);
		if (id < 10) {
			for (int j = 1; j < 5; j++) {
				c[j] = ' ';
			}
		}
		else if (id < 100) {
			for (int j = 2; j < 5; j++) {
				c[j] = ' ';
			}
		}
		else if (id < 1000) {
			for (int j = 3; j < 5; j++) {
				c[j] = ' ';
			}
		}
		else if (id < 10000) {
			for (int j = 4; j < 5; j++) {
				c[j] = ' ';
			}
		}
		return c[a];
	}

private:
	int id;
	string name;
};
