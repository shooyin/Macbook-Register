//John Le

#include "hashi.h"

#include <fstream>

hashi::hashi()
{
	loadDatabase();
}

void hashi::loadDatabase() {
	std::string username, password;
	std::ifstream logins("login_record.txt");

	// Fill Hash Table with Database
	if (logins.is_open()) {

		// Clear Hash Table
		for (int i = 0; i < TABLE_SIZE; i++) {
			HashTable[i] = new user;
			HashTable[i]->username = "empty";
			HashTable[i]->password = "empty";
			HashTable[i]->next = NULL;
		}

		while (logins >> username >> password) {
			addUser(username, password);
		}

		logins.close();
	}
	else std::cout << "Unable to open file\n";
}

bool hashi::hasDuplicate(std::string username)
{
	int index = Hash(username);

	if (HashTable[index]->username == "empty") {
		return false;
	}
	else {
		user* userPtr = HashTable[index];

		while (userPtr->next != NULL) {
			if (userPtr->username == username) {
				return true;
			}
			userPtr = userPtr->next;
		}
	}
	return false;
}

void hashi::addUser(std::string username, std::string password)
{
	bool duplicate = false;
	int index = Hash(username);

	// If bucket is empty = Add it to initial bucket
	if (HashTable[index]->username == "empty") {
		HashTable[index]->username = username;
		HashTable[index]->password = password;
	}
	else {	// Create temp node
		user* userPtr = HashTable[index];
		user* n = new user;
		n->username = username;
		n->password = password;
		n->next = NULL;

		// Traverse to end of bucket
		while (userPtr->next != NULL)
			userPtr = userPtr->next;

		userPtr->next = n;	// Add temp to the next pointer of the last node
	}
}

void hashi::addToTextFile(std::string username, std::string password)
{
	std::ofstream logins("login_record.txt", std::ios::app);

	if (logins.is_open())
		logins << "\n" << username << "\t" << password;
	else
		std::cout << "Unable to open file\n";

	logins.close();
}

bool hashi::confirmUser(std::string username, std::string password) {

	int index = Hash(username);			// Index of bucket

	user* findPtr = HashTable[index];	// Pointer, starting at top of bucket

										// Traverse
	while (findPtr != NULL && findPtr->username != username
		&& findPtr->password != password) {
		findPtr = findPtr->next;
	}

	// Case 1 - No match
	if (findPtr == NULL) {
		std::cout << username << " was not found\n";
		return false;
	}
	// Case 2 - Match
	else if(findPtr != NULL && (findPtr->username == username && findPtr->password == password)){
		std::cout << "Welcome, " << username << "!\n";
		return true;
	}
}

//Collisions?
int hashi::numberOfUsersInIndex(int index)
{
	int count = 0;

	if (HashTable[index]->username == "empty") {
		return count;
	}
	else {
		count++;
		user* userPtr = HashTable[index];

		while (userPtr->next != NULL) {
			count++;
			userPtr = userPtr->next;
		}
	}
	return count;
}

/*
Prints a layout of the hash table:
- Index
- Username of top bucket
- Password of top bucket
- # of users in bucket
*/
void hashi::printTable()
{
	int number;

	for (int i = 0; i < TABLE_SIZE; i++) {
		number = numberOfUsersInIndex(i);
		std::cout << "-----------------------\n";
		std::cout << "index = " << i << std::endl;
		std::cout << HashTable[i]->username << std::endl;
		std::cout << HashTable[i]->password << std::endl;
		std::cout << "# of users = " << number << std::endl;
		std::cout << "-----------------------\n";
	}
}

/*
Prints each user of specified bucket:
- Index of Bucket
- Username
- Password
*/
void hashi::printUsersInIndex(int index)
{
	user* userPtr = HashTable[index];

	if (userPtr->username == "empty") {
		std::cout << "index = " << index << " is empty\n";
	}
	else {
		std::cout << "index " << index << " contains the following items\n";

		while (userPtr != NULL) {
			std::cout << "--------------------------\n";
			std::cout << userPtr->username << std::endl;
			std::cout << userPtr->password << std::endl;
			std::cout << "--------------------------\n";
			userPtr = userPtr->next;

		}
	}
}

/*
Finds password of a specified username
Else, username not found
*/
void hashi::findPassword(std::string username)
{
	int index = Hash(username);					// Index of bucket
	bool found = false;							// Username finding condition
	std::string password;						// Password retrieval

	user* userPtr = HashTable[index];			// Start at top of bucket

	while (userPtr != NULL) {
		if (userPtr->username == username) {	//Found condition
			found = true;
			password = userPtr->password;
		}
		userPtr = userPtr->next;				// Traverse
	}

	if (found == true)
		std::cout << "Password: " << password << std::endl;
	else
		std::cout << username << " was not found" << std::endl;
}

/*
Remove particular username and password
*/
void hashi::removeUser(std::string username)
{
	int index = Hash(username);					// Index of bucket

	user* delPtr;
	user* userPtr1 = NULL;
	user* userPtr2 = NULL;

	// Case 0 - bucket is empty
	if (HashTable[index]->username == "empty" && HashTable[index]->password == "empty") {
		std::cout << username << " was not found\n";
	}

	// Case 1 - only 1 user contained in bucket and that user has matching name
	else if (HashTable[index]->username == username && HashTable[index]->next == NULL) {
		HashTable[index]->username == "empty";
		HashTable[index]->password = "empty";
		std::cout << username << " was removed\n";
	}

	// Case 2 - match is located in the first user in the bucket but there are more items
	// in the bucket
	else if (HashTable[index]->username == username) {
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;

		std::cout << username << " was removed\n";
	}

	//Case 3 - bucket contains items but first user is not a match
	else {
		userPtr1 = HashTable[index]->next;
		userPtr2 = HashTable[index];

		while (userPtr1 != NULL && userPtr1->username != username) {
			userPtr2 = userPtr1;
			userPtr1 = userPtr1->next;
		}
	}

	//Case 3.1 - no match
	if (userPtr1 == NULL) {
		std::cout << username << " was not found\n";
	}
	//Case 3.2 - match is found
	else {
		delPtr = userPtr1;
		userPtr1 = userPtr1->next;
		userPtr2->next = userPtr1;
		delete delPtr;

		std::cout << username << " was removed\n";
	}
}

void hashi::removeFromTextFile(std::string username, std::string password) {

	bool found = false;									// To avoid similar usernames
	std::string line;									// Traverses login_record.txt
	std::string search = username + "\t" + password;	// What we are looking for
	std::ifstream logins("login_record.txt");			// Original file
	std::ofstream temp("temp.txt");						// Temporary file

	if (logins.is_open() && temp.is_open()) {
		while (getline(logins, line)) {
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
	logins.close();
	remove("login_record.txt");
	rename("temp.txt", "login_record.txt");
}

int hashi::Hash(std::string key)
{
	int hash = 0;
	int index;

	for (size_t i = 0; i < key.length(); i++) {
		hash += (int)key[i];
	}

	index = hash % TABLE_SIZE;

	return index;
}