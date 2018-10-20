//Charles Canasa

#pragma once

#include "macBook.h"

#include <iostream>
#include <fstream>
#include <iomanip>


class fileIO : protected macBook
{
private:
	std::ifstream inputFile;
	std::string inPath;
	std::string inFile;
	std::ofstream outputFile;
	int count;
	int done;
	int check;


public:
	fileIO();
	~fileIO();

	//creates an array of macbooks reading from a file
	int readFile(macBook[]);
	//creates an output file of books in the inventory/can reuse same txt file
	void writeFile(macBook[], int);
	//adds to array
	int addMacBook(macBook[], int, macBook);
	//deletes from array
	int deleteMacBook(macBook[], int, macBook);
};