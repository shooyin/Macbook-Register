#pragma once

#include "macBook.h"

#include <iostream>
#include <string>

class macHash {
private:
	static const int TABLE_SIZE = 30;

	macBook* macTable[TABLE_SIZE];

public:
	//Default constructor
	macHash();

	int Hash(std::string Key);

	void loadDatabase();

	bool hasDuplicate(std::string);

	void addMac(macBook);
	void addToTextFile(macBook);

	bool searchMac(macBook);
	int numberOfMacsInIndex(int index);

	void printTable();
	void printMacsInIndex(int index);
	int numOfFilledEntries();
	int longestBucket();
	int numOfCollisions();
	int numOfCollisionsAt(int);

	//void findPassword(std::string username);

	void removeMac(macBook);
	void removeFromTextFile(macBook);
};