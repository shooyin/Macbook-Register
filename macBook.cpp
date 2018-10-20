//Charles Canasa

#include <iostream>
#include <string>
#include <fstream>

#include "macBook.h"

//Default Constructor
macBook::macBook()
{
	orderNum = "";
	name = "";
	releaseDate = "";
	price = 0.0;
	quantity = 0;
}

//Overloaded Constructor
macBook::macBook(std::string ord, std::string nam, std::string date, double pric, int quan)
{
	orderNum = ord;
	name = nam;
	releaseDate = date;
	price = pric;
	quantity = quan;

	std::cout << "Order Number: " << orderNum << "\nName: " << name << "\nRelease Date: " << releaseDate << "\nPrice: " << price << "\nQuantity: " << quantity << std::endl << std::endl;
}

macBook::~macBook()
{

}


//Setters
void macBook::setOrderNum(std::string ord)
{
	orderNum = ord;
}

void macBook::setName(std::string nam)
{
	name = nam;
}

void macBook::setReleaseDate(std::string date)
{
	releaseDate = date;
}

void macBook::setPrice(double pric)
{
	price = pric;
}

void macBook::setQuantity(int quan)
{
	quantity = quan;
}

void macBook::setNext(macBook* sNext)
{
	nextMac = sNext;
}

//Getters
std::string macBook::getOrderNum() const
{
	return orderNum;
}

std::string macBook::getName() const
{
	return name;
}

std::string macBook::getReleaseDate() const
{
	return releaseDate;
}

double macBook::getPrice() const
{
	return price;
}

int macBook::getQuantity() const
{
	return quantity;
}

macBook* macBook::getNext() const
{
	return nextMac;
}

//Overloaded comparison operators
bool macBook::operator < (const macBook &right)
{
	bool lessthan;

	if (orderNum < right.orderNum)
		lessthan = true;

	//else if (orderNum < right.orderNum || name < right.name || releaseDate < right.releaseDate || price < right.price || quantity < right.quantity)
		//lessthan = true;
	else
		lessthan = false;
	return lessthan;
}

bool macBook::operator > (const macBook &right)
{
	bool greaterthan;

	if (orderNum > right.orderNum)
		greaterthan = true;

	//else if (orderNum > right.orderNum || name > right.name || releaseDate > right.releaseDate || price > right.price || quantity > right.quantity)
		//greaterthan = true;
	else
		greaterthan = false;

	return greaterthan;
}

bool macBook::operator <= (const macBook &right)
{
	bool lessthanequal;

	if (*this < right || *this == right)
		lessthanequal = true;
	else
		lessthanequal = false;

	return lessthanequal;
}

bool macBook::operator >= (const macBook &right)
{
	bool greaterthanequal;

	if (*this > right || *this == right)
		greaterthanequal = true;
	else
		greaterthanequal = false;

	return greaterthanequal;
}

//Overloaded equality operators
bool macBook::operator == (const macBook &right)
{
	if (orderNum == right.orderNum)
		return true;
	else if (orderNum == right.orderNum && name == right.name && releaseDate == right.releaseDate && price == right.price)
		return true;
	else
		return false;
}

bool macBook::operator != (const macBook &right)
{
	if (*this == right)
		return false;
	else
		return true;
}

//Overloaded input/output operators feel free to change these
std::ostream &operator << (std::ostream &strm, const macBook &obj)
{
	strm << "Order Number: " << obj.orderNum << std::endl << "Name: " << obj.name << std::endl << "Release Date: " << obj.releaseDate << std::endl << "Price: " << obj.price << std::endl << "Quantity: " << obj.quantity << std::endl;

	return strm;
}

std::istream &operator >> (std::istream &strm, macBook &obj)
{
	std::cout << "Enter Order Number - ";
	getline(strm, obj.orderNum);

	std::cout << "Enter Name - ";
	getline(strm, obj.name);

	std::cout << "Enter Release Date - ";
	getline(strm, obj.releaseDate);

	std::cout << "Enter Price - ";
	strm >> obj.price;
	strm.ignore();

	std::cout << "Enter Quantity - ";
	strm >> obj.quantity;
	strm.ignore();

	return strm;
}