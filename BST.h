//Frankie Ranallo

#pragma once

#include <iostream>

#include "BSTNode.h"

template<class T>
class BST {
private:
	BSTNode<T>* root;
public:
	//constructors
	BST() {
		root = nullptr;
	}
	BST(T data) {
		root = new BSTNode<T>(data);
	}
	BST(BSTNode<T>* node) {
		root = node;
	}

	//destructor
	~BST() {
		deleteTree();
	}

	//getters and setters
	BSTNode<T>* getRootNode() {
		return root;
	}
	void setRootNode(BSTNode<T>* data) {
		root = data;
	}
	T getRootData() {
		return root->getData();
	}
	void setRootData(T data) {
		root->setData(data);
	}

	//Add
	/*
	node curr is equal to root
	node parent
	node toAdd is equal to a new node with data
	if root is equal to nullptr
	root is equal to toAdd
	else
	bool added is false
	do while added is false
	if curr is equal to nullptr
	if data is less than parent's data
	parent's left is equal to toAdd
	else
	parent's right is equal to toAdd
	added is equal to true
	else if data is less than curr's data
	parent is equal to curr
	curr is equal to curr's left
	else
	parent is equal to curr
	curr is equal to curr's right
	*/
	void add(T data) {
		BSTNode<T>* curr = root;
		BSTNode<T>* parent = root;
		BSTNode<T>* toAdd = new BSTNode<T>(data);
		if (root == nullptr) {//incase this is the first node to be added
			root = toAdd;
		}
		else {
			bool added = false;
			do {
				if (curr == nullptr) {//when the place that the node to be inserted has been found
					if (data < parent->getData()) {//if the data is less than the parents data
						parent->setLeft(toAdd);//the data goes to the left of the parent
					}
					else {
						parent->setRight(toAdd);//else the data is greater or equal than the parents data so it goes to the right
					}
					added = true;
				}
				else if (data < curr->getData()) {//if the data is less than curr's data
					parent = curr;
					curr = curr->getLeft();
				}
				else {//if the data is greater or equal to curr's data
					parent = curr;
					curr = curr->getRight();
				}

			} while (!added);
		}
	}

	void addByOrder(T data)
	{
		BSTNode<T>* curr = root;
		BSTNode<T>* parent = root;
		BSTNode<T>* toAdd = new BSTNode<T>(data);
		if (root == nullptr) {//incase this is the first node to be added
			root = toAdd;
		}
		else {
			bool added = false;
			do {
				if (curr == nullptr) {//when the place that the node to be inserted has been found
					if (data.getOrderNum() < parent->getData().getOrderNum()) {//if the data is less than the parents data
						parent->setLeft(toAdd);//the data goes to the left of the parent
					}
					else {
						parent->setRight(toAdd);//else the data is greater or equal than the parents data so it goes to the right
					}
					added = true;
				}
				else if (data.getOrderNum() < curr->getData().getOrderNum()) {//if the data is less than curr's data
					parent = curr;
					curr = curr->getLeft();
				}
				else {//if the data is greater or equal to curr's data
					parent = curr;
					curr = curr->getRight();
				}

			} while (!added);
		}
	}

	//isEmpty
	bool isEmpty() {
		if (root == nullptr) {
			return true;
		}
		return false;
	}

	//count
	/*
	num is equal to 1
	if node has a left
	num plus count of node's left
	end if
	if node has a right
	num plus count of node's right
	end if
	return num
	*/
	int count() {
		return count(root);
	}
	int count(BSTNode<T>* node) {
		int num = 1;
		if (node->hasLeft()) {
			num += count(node->getLeft());
		}
		if (node->hasRight()) {
			num += count(node->getRight());
		}
		return num;
	}

	//Has
	//returns true if the tree has the data that is passed
	/*
	node curr is equal to root
	do while curr is not equal to nullptr
	if data is equal to curr's data
	return true
	else if data is less than curr's data
	curr is equal to curr's left
	else if data is greater than curr's data
	curr is equal to curr's right
	end if
	end loop
	return false
	*/
	bool has(T data) {
		BSTNode<T>* curr = root;
		do {
			if (data == curr->getData()) {
				return true;
			}
			else if (data < curr->getData()) {
				curr = curr->getLeft();
			}
			else if (data > curr->getData()) {
				curr = curr->getRight();
			}
		} while (curr != nullptr);
		return false;
	}

	//whereIs
	//whereIs returns the position of a data member in order relative to the staring node
	/*
	whereIs
	if the node has the data
	at equals 1
	incrementInorder of the node, pointer at and the data
	return at
	end if
	return 0;
	incrementInorder
	found equals false
	if node has a left
	found equals incrementInorder of node's left, at and data
	if found equals true
	return found
	end if
	at plus 1
	end if
	if data is equal to node's data
	return true
	end if
	if node has a right
	at plus 1
	found equals incrementInorder of node'sright, at and data
	end if
	return found
	*/
	int whereIs(T data) {
		return whereIs(root, data);
	}
	int whereIs(BSTNode<T>* node, T data) {
		if (has(data)) {
			int at = 1;
			incrementInorder(node, &at, data);
			return at;
		}
		return 0;
	}
	bool incrementInorder(BSTNode<T>* node, int* at, T data) {
		bool found = false;
		if (node->hasLeft()) {
			found = incrementInorder(node->getLeft(), at, data);
			if (found) {
				return found;
			}
			*at += 1;
		}
		if (data == node->getData()) {
			return true;
		}
		if (node->hasRight()) {
			*at += 1;
			found = incrementInorder(node->getRight(), at, data);
		}
		return found;
	}

	//Find
	/*
	find smallest
	node curr is equal to node
	small is equal to curr's data
	while curr has left
	small is equal to curr's data
	curr is equal to curr's left
	end loop
	return small
	the same for find largest but wiht left and right reversed
	*/
	T findSmallest() {
		return findSmallest(root);
	}
	T findSmallest(BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		T small = curr->getData();
		do {
			curr = curr->getLeft();
			small = curr->getData();
		} while (curr->hasLeft());
		return small;
	}

	T findLargest() {
		return findLargest(root);
	}
	T findLargest(BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		T large = curr->getData();
		do {
			curr = curr->getRight();
			large = curr->getData();
		} while (curr->hasRight());
		return large;
	}

	//findAt
	//finds the node at the specified position relative to the one passed in an inorder fasion
	/*
	//findAt
	num is equal to the count of nodes including and descending from node
	at is equal to 1
	if position is less than or equal to num
	return findInorder of node, at, and position
	end if
	return NULL
	//findInorder
	data is equal to NULL
	if node has left
	data is equal to findInorder of node's left, at and posistion
	if data is not equal to NULL
	return data
	end if
	pointer at plus 1
	end if
	if at is equal to position
	return node's data
	end if
	if node has right
	pointer at plus 1
	data is equal to findInorder of node's right, at. and position
	end if
	return data
	*/
	T findAt(int pos) {
		return findAt(root, pos);
	}
	T findAt(BSTNode<T>* node, int pos) {
		int num = count(node);
		int at = 1;
		if (pos <= num) {
			return findInorder(node, &at, pos);
		}
		else
			return data;
	}
	T findInorder(BSTNode<T>* node, int* at, int pos) {
		T data = NULL;
		if (node->hasLeft()) {
			data = findInorder(node->getLeft(), at, pos);
			if (data != NULL) {
				return data;
			}
			*at += 1;
		}
		if (*at == pos) {
			return node->getData();
		}
		if (node->hasRight()) {
			*at += 1;
			data = findInorder(node->getRight(), at, pos);
		}
		return data;
	}


	//Remove
	/*
	node is passed
	Template data is equal to findSmallest from the node
	deleteSmallest from the node
	return data
	same for remove largest but opposite
	*/
	T removeSmallest() {
		return removeSmallest(root);
	}
	T removeSmallest(BSTNode<T>* node) {
		T data;
		data = findSmallest(node);
		deleteSmallest(node);
		return data;
	}
	T removeLargest() {
		return removeLargest(root);
	}
	T removeLargest(BSTNode<T>* node) {
		T data;
		data = findLargest(node);
		deleteLargest(node);
		return data;
	}

	T removeAt(int pos) {
		return removeAt(root, pos);
	}
	T removeAt(BSTNode<T>* node, int pos) {
		T data = findAt(node, pos);
		deleteAt(node, pos);
		return data;
	}


	//Pluck
	/*
	node curr is equal to node
	node parent is equal to node's parent
	while curr has left
	parent is equal to curr
	curr is equal to curr's left
	end loop
	if parent's data is less than or equal to curr's data
	parent's right is equal to curr's right
	else
	parent's left is equal to curr's right
	end if
	curr's right is equal to nullptr
	return curr
	same for pluckLargest but opposite
	*/
	BSTNode<T>* pluckSmallest(BSTNode<T>* par, BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		BSTNode<T>* parent = par;
		while (curr->hasLeft()) {
			parent = curr;
			curr = curr->getLeft();
		}
		if (parent->getData() <= curr->getData()) {
			parent->setRight(curr->getRight());
		}
		else {
			parent->setLeft(curr->getRight());
		}
		curr->setRight(nullptr);
		return curr;
	}
	BSTNode<T>* pluckLargest(BSTNode<T>* par, BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		BSTNode<T>* parent = par;
		while (curr->hasRight()) {
			parent = curr;
			curr = curr->getRight();
		}
		if (parent->getData() <= curr->getData()) {
			parent->setRight(curr->getLeft());
		}
		else {
			parent->setLeft(curr->getLeft());
		}
		curr->setLeft(nullptr);
		return curr;
	}


	//Delete
	/*
	delete smallest
	node curr is equal to node
	node parent is equal to node
	while curr has left
	parent is equal to curr
	curr is euqla to curr's left
	end loop
	if curr is equal to root
	if root has right
	root is equal to root's right
	else
	root is equal to nullptr
	end if
	else
	if curr has right
	parent's left is set to curr's right
	else
	parent's left is set to nullptr
	end if
	end if
	delete curr
	the same for delete largest but with left and right reversed
	*/
	void deleteSmallest() {
		deleteSmallest(root);
	}
	void deleteSmallest(BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		BSTNode<T>* parent = node;
		while (curr->hasLeft()) {
			parent = curr;
			curr = curr->getLeft();
		}
		if (curr == root) {
			if (root->hasRight()) {
				root = root->getRight();
			}
			else {
				root = nullptr;
			}
		}
		else {
			if (curr->hasRight()) {
				parent->setLeft(curr->getRight());
			}
			else {
				parent->setLeft(nullptr);
			}
		}
		delete curr;
	}
	void deleteLargest() {
		deleteLargest(root);
	}
	void deleteLargest(BSTNode<T>* node) {
		BSTNode<T>* curr = node;
		BSTNode<T>* parent = node;
		while (curr->hasRight()) {
			parent = curr;
			curr = curr->getRight();
		}
		if (curr == root) {
			if (root->hasLeft()) {
				root = root->getLeft();
			}
			else {
				root = nullptr;
			}
		}
		else {
			if (curr->hasLeft()) {
				parent->setRight(curr->getLeft());
			}
			else {
				parent->setRight(nullptr);
			}
		}
		delete curr;
	}

	//DeleteData
	/*
	if start has the data
	node curr is equal to start
	node parent is equal to start
	bool found is false
	do while not found
	if data is equal to curr's data
	found is equal to true
	else if data is less than curr's data
	parent is equal to curr
	curr is equal to curr's left
	else
	parent is equal to curr
	curr is equal to curr's right
	end if
	end loop
	if data is equal to root's data
	if root has right
	root's data is equal to findSmallest of root's right
	deleteSmallest of root's right
	else if root has left
	root's data is equal to findLargest of root's left
	deleteLargest fo root's left
	else if root is a leaf
	root is equal to nullptr
	end if
	else
	if curr has right
	node is equal to pluckSmallest of curr's right
	node's right is equal to curr's right
	node's left is equal to curr's left
	if parent's data is less than curr's data
	parent's right is equal to node
	else
	parent's left is equal to node
	end if
	else if curr has left
	node is equal to pluckLargest of curr's left
	node's left is equal to curr's left
	node's right is equal to curr's right
	if parent's data is less than curr's data
	parent's right is equal to node
	else
	parent's left is equal to node
	end if
	else if curr is a leaf
	if parent's data is less than curr's data
	parent's right is equal to nullptr
	else
	parent's left is equal to nullptr
	end if
	end if
	delete curr
	end if
	end if
	*/
	void deleteData(T data) {
		deleteData(root, data);
	}
	void deleteData(BSTNode<T>* start, T data) {
		if (this->has(data)) {
			BSTNode<T>* curr = start;
			BSTNode<T>* parent = start;
			bool found = false;
			do {
				if (data == curr->getData()) {
					found = true;
				}
				else if (data < curr->getData()) {
					parent = curr;
					curr = curr->getLeft();
				}
				else {
					parent = curr;
					curr = curr->getRight();
				}
			} while (!found);

			if (data == root->getData()) {
				if (root->hasRight()) {
					BSTNode<T>* node = pluckSmallest(curr, curr->getRight());
					node->setRight(curr->getRight());
					node->setLeft(curr->getLeft());
					root = node;
				}
				else if (root->hasLeft()) {
					BSTNode<T>* node = pluckLargest(curr, curr->getLeft());
					node->setLeft(curr->getLeft());
					node->setRight(curr->getRight());
					root = node;
				}
				else if (root->isLeaf()) {
					root = nullptr;
				}
			}
			else {
				if (curr->hasRight()) {
					BSTNode<T>* node = pluckSmallest(curr, curr->getRight());
					node->setRight(curr->getRight());
					node->setLeft(curr->getLeft());
					if (parent->getData() < curr->getData()) {
						parent->setRight(node);
					}
					else {
						parent->setLeft(node);
					}
				}
				else if (curr->hasLeft()) {
					BSTNode<T>* node = pluckLargest(curr, curr->getLeft());
					node->setLeft(curr->getLeft());
					node->setRight(curr->getRight());
					if (parent->getData() < curr->getData()) {
						parent->setRight(node);
					}
					else {
						parent->setLeft(node);
					}
				}
				else if (curr->isLeaf()) {
					if (parent->getData() < curr->getData()) {
						parent->setRight(nullptr);
					}
					else {
						parent->setLeft(nullptr);
					}
				}
			}
			delete curr;
		}
	}

	//DeleteAt
	//deletes a node at the specified position relative to the initial node passed
	void deleteAt(int pos) {
		deleteAt(root, pos);
	}
	void deleteAt(BSTNode<T>* node, int pos) {
		T data = findAt(node, pos);
		deleteData(node, data);
	}

	//DeleteTree
	/*
	deletePostorder
	if node has left
	deletePostorder of node's left
	end if
	if node has right
	deletePostorder of node's right
	end if
	delete node
	*/
	void deleteTree() {
		deletePostorder(root);
	}
	void deletePostorder(BSTNode<T>* node) {
		if (node->hasLeft()) {
			deletePostorder(node->getLeft());
		}
		if (node->hasRight()) {
			deletePostorder(node->getRight());
		}
		delete node;
	}


	//Print
	void print() {
		printInorder(root);//calls inorder print
	}

	//printInorder
	/*
	if node has left
	printInorder of node's left
	end if
	print node's data
	next line
	if node has right
	printInorder of node's right
	end if
	*/
	void printInorder(BSTNode<T>* node) {
		if (node->hasLeft()) {
			printInorder(node->getLeft());
		}
		node->printData();
		cout << endl;

		if (node->hasRight()) {
			printInorder(node->getRight());
		}
	}

	//printIndented
	/*
	for i is 0; i is less than tab; i++
	print an indent
	end loop
	print node data
	next line
	if node has left
	printPreorder of node's left, adding 1 to tab
	end if
	if node has right
	printPreorder of node's right, adding 1 to tab
	end if
	*/
	void printIndented() {
		printPreorder(root, 0);
	}
	void printPreorder(BSTNode<T>* node, int tab) {
		for (int i = 0; i < tab; i++) {
			cout << "\t";
		}
		node->printData();
		cout << endl;
		if (node->hasLeft()) {
			printPreorder(node->getLeft(), tab + 1);
		}
		if (node->hasRight()) {
			printPreorder(node->getRight(), tab + 1);
		}
	}

	//printAt
	//prints the data of the node at the specified inorder position relative to the starting node
	/*
	printAt
	num equals count of the node
	at equals 1
	if pos is less than or equal to num
	printSearch of node, pos and pointer at
	end if
	printSearch
	printed equals false
	if node has left
	printed equals printSearch of node's left, pos and at
	if printed equals true
	return printed
	end if
	at plus 1
	end if
	if at is equal to pos
	print node's data
	return true
	end if
	if node has right
	at plus 1
	printed equals printSearch of node's right, pos and at
	end if
	return printed
	*/
	void printAt(int pos) {
		printAt(root, pos);
	}
	void printAt(BSTNode<T>* node, int pos) {
		int num = count(node);
		int at = 1;
		if (pos <= num) {
			printSearch(node, pos, &at);
		}
	}
	bool printSearch(BSTNode<T>* node, int pos, int* at) {
		bool printed = false;
		if (node->hasLeft()) {
			printed = printSearch(node->getLeft(), pos, at);
			if (printed) {
				return printed;
			}
			*at += 1;
		}
		if (*at == pos) {
			node->printData();
			return true;
		}
		if (node->hasRight()) {
			*at += 1;
			printed = printSearch(node->getRight(), pos, at);
		}
		return printed;
	}
};