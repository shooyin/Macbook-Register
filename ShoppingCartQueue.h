#pragma once

#include <iostream>

template <class T>
class Node {
private:
	T item;
	Node<T>* next;

public:
	Node() {
		next = nullptr;
	}

	Node(const T& anItem)
	{
		item = anItem;
		next = nullptr;
	}    // end constructor

	Node(const T& anItem,
		Node<T> *nextNodePtr) :
		item(anItem),
		next(nextNodePtr)
	{

	} // end constructor

	Node(const Node& copy)
	{
		item = copy.item;
		next = copy.next;
	}

	virtual ~Node()
	{
	}

	void setItem(const T& anItem)
	{
		item = anItem;
	}    // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}    //end setNext

	T getItem()
	{
		return item;
	}    //end getItem

	Node<T>* getNext() const
	{
		return next;
	}    //end getNext

	friend std::ostream& operator << (std::ostream &ostream, Node<T> outNode)
	{
		ostream << outNode.item;
		return ostream;
	}
};

//Linked List

template<class T>
class Link
{
private:
	Node<T> *head;    // Pointer to first node
	Node<T> *tail;
	int count;        // Current count of items

public:
	Link()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	virtual ~Link()
	{

	}

	int getCount() const
	{
		return count;
	}

	void setCount(int num)
	{
		count = num;
	}

	bool isEmpty() const
	{
		if (head == NULL)
			return true;
		else
			return false;
	}

	void add(const T& newEntry)
	{
		Node<T> *temp = new Node<T>(newEntry);

		if (isEmpty()) {
			head = temp;
			tail = temp;
		}
		else {
			tail->setNext(temp);
			tail = temp;
			tail->setNext(nullptr);
		}
		count++;
	}

	void addFront(T newEntry)
	{
		Node<T> *temp = new Node<T>(newEntry);

		if (count != 0) {
			temp->setNext(head);
			head = temp;
		}
		else {
			head = temp;
			tail = temp;
		}
		count++;
	}

	void addLast(T newEntry)
	{
		Node<T> *temp = new Node<T>(newEntry);

		if (count != 0) {
			head->setNext(tail);
			tail->setNext(temp);
			tail = temp;
		}
		else {
			temp = head;
			temp = tail;
		}
		count++;
	}

	bool remove(const T& anEntry)
	{
		Node<T> *current = head;
		Node<T>* nxt = head->getNext();

		while (current != NULL) {
			if (current->getItem() == anEntry) {
				break;
			}
			else {    // Continue to the next node
				current = nxt;
				nxt = nxt->getNext();
			}
		}
		if (current == NULL) {
			// Either list is empty or we reached the end not found
		}
		else {    // Deleting current
			head = nxt;
			delete nxt;
			count--;
			return true;
		}
		return false;
	}

	bool removeFirst() {
		if (getCount() != 0)
			head = head->getNext();
		else
			return false;

		return true;
	}

	void clear()
	{
		Node<T> *current = head;
		Node<T> *next = new Node<T>();

		while (current != NULL) {
			next = current->getNext();
			delete current;
			current = next;
		}
		head = nullptr;
		count = 0;
	}

	bool contains(const T& anEntry) const
	{
		Node<T> *current = head;
		Node<T> *next = current->getNext();
		Node<T> *find = new Node<T>(anEntry);

		while (current != NULL) {
			if (current->getItem() == find->getItem()) {
				delete current;
				return true;
			}
			else
				current->setItem(next->getItem());
		}
		delete current;
		return false;
	}

	void print() {    // try to print each amount of each object here
		Node<T>* temp = new Node<T>();
		temp = head;
		while (temp != nullptr)
		{
			std::cout << temp->getItem() << std::endl;
			temp = temp->getNext();
		}
	}

	Node<T>* getHead() const
	{
		return head;
	}

	Node<T>* getTail() const
	{
		return tail;
	}
};

//Queue
template<class T>
class ShoppingCartQueue : private Link<T>
{
private:

public:
	//Default constructor
	ShoppingCartQueue()
	{
	}

	//Destructor
	~ShoppingCartQueue()
	{

	}


	bool isEmpty() const
	{
		if (Link<T>::getHead() == nullptr)
			return true;
		else
			return false;
	}

	void enqueue(const T& newEntry)
	{
		if (isEmpty())
		{
			Link<T>::add(newEntry);
		}
		else
		{
			Link<T>::addLast(newEntry);
		}
	}

	bool dequeue()
	{
		if (!isEmpty())
		{
			Link<T>::removeFirst();
		}
		else
		{
			return false;
		}
		return true;
	}

	void print()
	{
		Node<T>* temp = new Node<T>();
		temp = Link<T>::getHead();
		while (temp != nullptr)
		{
			std::cout << temp->getItem() << std::endl;
			temp = temp->getNext();
		}
	}

	Node<T> peekFront()
	{
		return *Link<T>::getHead();
	}

	Node<T> peekRear()
	{
		return *Link<T>::getTail();
	}
};
