//Charles Canasa

#pragma once

#include <iostream>
#include <string>
#include <fstream>

class macBook
{
protected:
	std::string orderNum;
	std::string name;
	std::string releaseDate;
	double price;
	int quantity;
	macBook* nextMac;

public:

	//Default Constructor
	macBook();

	//Overloaded constructor
	macBook(std::string, std::string, std::string, double, int);

	//Destructor
	~macBook();

	//Setters
	void setOrderNum(std::string);
	void setName(std::string);
	void setReleaseDate(std::string);
	void setPrice(double);
	void setQuantity(int);
	void setNext(macBook*);

	//Getters
	std::string getOrderNum() const;
	std::string getName() const;
	std::string getReleaseDate() const;
	double getPrice() const;
	int getQuantity() const;
	macBook* getNext() const;

	//Overloaded comparison operators
	bool operator < (const macBook &);
	bool operator > (const macBook &);

	bool operator <= (const macBook &);
	bool operator >= (const macBook &);

	//Overloaded equality operators
	bool operator == (const macBook &);
	bool operator != (const macBook &);

	//Overloaded input/output operators feel free to change these
	friend std::ostream &operator << (std::ostream &, const macBook &);
	friend std::istream &operator >> (std::istream &, macBook &);

	//did this to allow fileIO access to the protected members/change if a better way
	friend class fileIO;
};