#include "macHash.h"
#include "fileIO.h"

//Default constructor
macHash::macHash()
{
	loadDatabase();
}

void macHash::loadDatabase()
{
	macBook catalog[TABLE_SIZE];
	fileIO macFile;
	macFile.readFile(catalog);

	// Clear Hash Table
	for (int i = 0; i < TABLE_SIZE; i++) {
		macTable[i] = new macBook;
		macTable[i]->setOrderNum("");
		macTable[i]->setName("");
		macTable[i]->setReleaseDate("");
		macTable[i]->setPrice(0.0);
		macTable[i]->setQuantity(0);
		macTable[i]->setNext(NULL);
	}

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		addMac(catalog[i]);
	}
}

void macHash::addMac(macBook newMac)
{
	bool duplicate = false;

	int index = Hash(newMac.getOrderNum());

	// If bucket is empty = Add it to initial bucket
	if (macTable[index] != NULL && macTable[index]->getOrderNum() == "") {
		macTable[index]->setOrderNum(newMac.getOrderNum());
		macTable[index]->setName(newMac.getName());
		macTable[index]->setReleaseDate(newMac.getReleaseDate());
		macTable[index]->setPrice(newMac.getPrice());
		macTable[index]->setQuantity(newMac.getQuantity());
	}
	else {	// Create temp node
		macBook* macPtr = macTable[index];
		macBook* n = new macBook;
		n->setOrderNum(newMac.getOrderNum());
		n->setName(newMac.getName());
		n->setReleaseDate(newMac.getReleaseDate());
		n->setPrice(newMac.getPrice());
		n->setQuantity(newMac.getQuantity());
		n->setNext(NULL);

		// Traverse to end of bucket
		if (macPtr != NULL)
		{
			while (macPtr->getNext() != NULL)
				macPtr = macPtr->getNext();

			macPtr->setNext(n);	// Add temp to the next pointer of the last node
		}
		else
		{
			macTable[index] = n;
		}
	}
}


int macHash::Hash(std::string key)
{
	int hash = 0;
	int index;

	for (size_t i = 0; i < key.length(); i++) {
		hash += (int)key[i];
	}

	index = hash % TABLE_SIZE;

	return index;
}

bool macHash::hasDuplicate(std::string orderNum)
{
	int index = Hash(orderNum);

	if (macTable[index]->getOrderNum() == "") {
		return false;
	}
	else {
		macBook* macPtr = macTable[index];

		while (macPtr->getNext() != NULL) {
			if (macPtr->getOrderNum() == orderNum) {
				return true;
			}
			macPtr = macPtr->getNext();
		}
	}
	return false;
}

void macHash::addToTextFile(macBook addTextMac)
{
	std::ofstream appleFile("apple.txt", std::ios::app);

	if (appleFile.is_open())
		appleFile << "\n" << addTextMac;
	else
		std::cout << "Unable to open file\n";

	appleFile.close();
}

bool macHash::searchMac(macBook searchMac) {

	int index = Hash(searchMac.getOrderNum());			// Index of bucket

	macBook* findPtr = macTable[index];	// Pointer, starting at top of bucket

										// Traverse
	while (findPtr != NULL && *findPtr != searchMac) {
		findPtr = findPtr->getNext();
	}

	// Case 1 - No match
	if (findPtr == NULL) {
		std::cout << searchMac << " was not found\n";
		return false;
	}
	// Case 2 - Match
	else {
		std::cout << searchMac << " was found !\n";
		return true;
	}
}

int macHash::numberOfMacsInIndex(int index)
{
	int count = 0;

	if (macTable[index]->getOrderNum() == "") {
		return count;
	}
	else {
		count++;
		macBook* macPtr = macTable[index];

		while (macPtr->getNext() != NULL) {
			count++;
			macPtr = macPtr->getNext();
		}
	}
	return count;
}

/*
Prints a layout of the hash table:
- Index
-Mac of top bucket
- # of macs in bucket
*/
void macHash::printTable()
{
	int number;

	for (int i = 0; i < TABLE_SIZE; i++) {
		number = numberOfMacsInIndex(i);
		std::cout << "-----------------------\n";
		std::cout << "index = " << i << std::endl;

		if (number > 1)
			printMacsInIndex(i);
		else
		{
			std::cout << *macTable[i] << std::endl;
			std::cout << "# of macs = " << number << std::endl;
			std::cout << "-----------------------\n";
		}
	}
}

/*
Prints each mac of specified bucket:
- Index of Bucket
- Mac
*/
void macHash::printMacsInIndex(int index)
{
	macBook* macPtr = macTable[index];

	if (macPtr->getOrderNum() == "") {
		std::cout << "index = " << index << " is empty\n";
	}
	else {
		std::cout << "index " << index << " contains the following items\n";

		while (macPtr != NULL) {
			std::cout << "--------------------------\n";
			std::cout << *macPtr << std::endl;
			std::cout << "--------------------------\n";
			macPtr = macPtr->getNext();

		}
	}
}

//Calculates number of entries that are filled in the hash table
int macHash::numOfFilledEntries()
{
	int filledEntries = 0;
	macBook compareNullObj;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (*macTable[i] != compareNullObj)
			filledEntries++;
	}
	return filledEntries;
}

//Calculates longest bucket in the table
int macHash::longestBucket()
{
	int bucketIndex = -1;
	int mostCol = numOfCollisionsAt(0);

	for (int i = 1; i < TABLE_SIZE; i++)
	{

		if (mostCol < numOfCollisionsAt(i))
		{
			mostCol = numOfCollisionsAt(i);
			bucketIndex = i;
		}
	}
	return bucketIndex;
}

//Calculates total number of collisions in the entire table
int macHash::numOfCollisions()
{
	int collisions = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (macTable[i]->getNext() != nullptr)
			collisions++;
	}
	return collisions;
}

//Calculates number of collisions at a specified index
int macHash::numOfCollisionsAt(int arrIndex)
{
	int collisions = 0;
	if (macTable[arrIndex]->getNext() != nullptr)
		collisions++;
	return collisions;
}

/*
Remove particular mac
*/
void macHash::removeMac(macBook removeMac)
{
	int index = Hash(removeMac.getOrderNum());					// Index of bucket

	macBook* delMacPtr;
	macBook* macPtr1 = NULL;
	macBook* macPtr2 = NULL;

	// Case 0 - bucket is empty
	if (macTable[index]->getOrderNum() == "") {
		std::cout << removeMac << " was not found\n";
	}

	// Case 1 - only 1 user contained in bucket and that user has matching name
	else if (macTable[index]->getOrderNum() == removeMac.getOrderNum() && macTable[index]->getNext() == NULL) {
		delMacPtr = macTable[index];
		macTable[index]->setOrderNum("");
		macTable[index]->setName("");
		macTable[index]->setReleaseDate("");
		macTable[index]->setPrice(0.0);
		macTable[index]->setQuantity(0);
		//std::cout << *macTable[index] << " was removed\n";
		return;
	}

	// Case 2 - match is located in the first user in the bucket but there are more items
	// in the bucket
	else if (macTable[index]->getOrderNum() == removeMac.getOrderNum()) {
		delMacPtr = macTable[index];
		macTable[index] = macTable[index]->getNext();
		delete delMacPtr;
		return;

		//std::cout << *macTable[index] << " was removed\n";
	}

	//Case 3 - bucket contains items but first user is not a match
	else {
		macPtr1 = macTable[index]->getNext();
		macPtr2 = macTable[index];

		while (macPtr1 != NULL && macPtr1->getOrderNum() != removeMac.getOrderNum()) {
			macPtr2 = macPtr1;
			macPtr1 = macPtr1->getNext();
		}
	}

	//Case 3.1 - no match
	if (macPtr1 == NULL) {
		std::cout << removeMac << " was not found\n";
	}
	//Case 3.2 - match is found
	else {
		delMacPtr = macPtr1;
		macPtr1 = macPtr1->getNext();
		macPtr2->setNext(macPtr1);
		delete delMacPtr;

		std::cout << removeMac << " was removed\n";
	}
}

void macHash::removeFromTextFile(macBook removeMac) {

	bool found = false;									// To avoid similar usernames
	std::string line;									// Traverses login_record.txt
	std::string search = removeMac.getOrderNum() + "\n" + removeMac.getName() + "\n" + removeMac.getReleaseDate() + "\n" + std::to_string(removeMac.getPrice()) + "\n" + std::to_string
		(removeMac.getQuantity());	// What we are looking for
	std::ifstream apples("apple.txt");		// Original file
	std::ofstream temp("temp.txt");						// Temporary file

	if (apples.is_open() && temp.is_open()) {
		while (getline(apples, line)) {
			// Add each line from original file to temp,
			// Unless if we found the line
			if (line == search && found == false) {
				line.replace(line.begin(), line.end(), "");
				found = true;
			}
			else
				temp << line << std::endl;
		}
	}
	else
		// Someone tampered the original files... -_-
		std::cout << "One of the txt is not found";

	temp.close();
	apples.close();
	remove("login_record.txt");
	rename("temp.txt", "login_record.txt");
}