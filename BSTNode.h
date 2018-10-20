/*templated binary search tree node
Frankie Ranallo
*/

#pragma once

#include <iostream>

template<class T>
class BSTNode {
private:
	T data;
	BSTNode<T>* left;//lesser value than data
	BSTNode<T>* right;//greater or equal value than data
public:
	//constructors
	BSTNode() {
		data = NULL;
		left = nullptr;
		right = nullptr;
	}
	BSTNode(T d) {
		data = d;
		left = nullptr;
		right = nullptr;
	}
	BSTNode(T d, BSTNode<T>* l, BSTNode<T>* r) {
		data = d;
		left = l;
		right = r;
	}

	//getters and setters
	T getData() {
		return data;
	}
	void setData(T d) {
		data = d;
	}
	BSTNode<T>* getLeft() {
		return left;
	}
	void setLeft(BSTNode<T>* l) {
		left = l;
	}
	BSTNode<T>* getRight() {
		return right;
	}
	void setRight(BSTNode<T>* r) {
		right = r;
	}

	bool isLeaf() {
		if (left == nullptr && right == nullptr) {
			return true;
		}
		return false;
	}
	bool hasChildren() {
		if (left != nullptr || right != nullptr) {
			return true;
		}
		return false;
	}
	bool hasLeft() {
		if (left != nullptr) {
			return true;
		}
		return false;
	}
	bool hasRight() {
		if (right != nullptr) {
			return true;
		}
		return false;
	}

	//print
	void printData() {
		cout << data;
	}
	void printLeft() {
		left->printData();
	}
	void printLeftAddress() {
		cout << left;
	}
	void printRight() {
		right->printData();
	}
	void printRightAddress() {
		cout << right;
	}
	void printAll() {
		cout << "Data: " << data << endl;
		cout << "\tleft: ";
		left->printData();
		cout << endl;
		cout << "\tright: ";
		right->printData();
		cout << endl;
	}
};