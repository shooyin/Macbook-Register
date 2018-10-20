//Charles Canasa
#include "BST.h"
#include "macHash.h"
#include "fileIO.h"

fileIO::fileIO()
{
	inPath = "";
	inFile = "apple.txt";
	count = 0;
	done = 0;
}

fileIO::~fileIO()
{

}

int fileIO::readFile(macBook catalog[])	//opens file of apple data and inserts into macbook object
{
	//Opens input file where .cpp file is
	inputFile.open(inFile);

	//Directs to file if initial input file can't be found/opened
	while (inputFile.fail())
	{
		inputFile.clear();
		std::cout << "File not found, please enter the folder path where your input file is located.\n(e.g. 'C:\\Users\\')\n";
		getline(std::cin, inPath);
		std::cout << "Now enter the file name including its extension.\n(e.g. 'name.txt')\n";
		getline(std::cin, inFile);
		inputFile.open(inPath + inFile);
	}

	while (inputFile)
	{
		//Inserts each line into corresponding object attribute
		getline(inputFile, orderNum);
		catalog[count].setOrderNum(orderNum);

		getline(inputFile, name);
		catalog[count].setName(name);

		getline(inputFile, releaseDate);
		catalog[count].setReleaseDate(releaseDate);

		inputFile >> price;
		inputFile.ignore();
		catalog[count].setPrice(price);

		inputFile >> quantity;
		inputFile.ignore();
		catalog[count].setQuantity(quantity);

		count++;

		/*	if (inputFile.eof())
		{
		done++;
		}*/
	}
	inputFile.close();

	/*
	//check if books are read correctly without using overloaded <<
	for (int i = 0; i < count; i++)
	{
	std::cout << catalog[i].orderNum << std::endl;
	std::cout << catalog[i].name << std::endl;
	std::cout << catalog[i].releaseDate << std::endl;
	std::cout << catalog[i].price << std::endl;
	std::cout << catalog[i].quantity << std::endl;
	}
	*/

	return count;
}


void fileIO::writeFile(macBook catalog[], int size)
{
	//if you dont want initial mac inventory rewritten
	outputFile.open("output.txt");

	//rewrites initial text file
	//outputFile.open(inPath + inFile);

	//writes inventory into file
	for (int i = 0; i < size; i++)
	{
		outputFile << catalog[i].orderNum << std::endl;
		outputFile << catalog[i].name << std::endl;
		outputFile << catalog[i].releaseDate << std::endl;
		outputFile << catalog[i].price << std::endl;
		outputFile << catalog[i].quantity;
		//prevents an extra empty line at the end avoiding a bad reusable file
		if (i != size - 1)
		{
			outputFile << std::endl;
		}
	}

	outputFile.close();
}


int fileIO::addMacBook(macBook catalog[], int size, macBook add)
{
	//initializes check
	check = false;

	//counts for the array of macbooks
	for (int i = 0; i < size; i++)
	{
		//if order number already exist, adds quantity to existing macbook
		if ((add.orderNum == catalog[i].orderNum) && (check == false))
		{
			std::cout << "Adding quantity to existing book. Previous quantity:\n";
			std::cout << "Order Number: " << catalog[i].orderNum << std::endl;
			std::cout << "Name: " << catalog[i].name << std::endl;
			std::cout << "Quantity: " << catalog[i].quantity << std::endl;
			catalog[i].quantity += quantity;
			std::cout << "Updated quantity:\n";
			std::cout << "Order Number: " << catalog[i].orderNum << std::endl;
			std::cout << "Name: " << catalog[i].name << std::endl;
			std::cout << "Quantity: " << catalog[i].quantity << std::endl << std::endl;
			return size;
		}

		else if (check == true)
		{
			//prevents the other options, couldnt think of a better way logically, for loops are weird
		}
		//if no similar macbook exists, creates new macbook at the end of the array
		else if (i == size - 1)
		{
			catalog[size].setOrderNum(add.orderNum);
			catalog[size].setName(add.name);
			catalog[size].setReleaseDate(add.releaseDate);
			catalog[size].setPrice(add.price);
			catalog[size].setQuantity(add.quantity);

			size++;
			check = true; // lets loop continue without repeating this option
		}
	}

	return size;
}

int fileIO::deleteMacBook(macBook catalog[], int size, macBook del)
{
	check = false;

	//checks and deletes entry if matching order number
	for (int i = 0; i < size; i++)
	{
		if ((del.orderNum == catalog[i].orderNum))
		{
			std::cout << "Deleting\n";
			std::cout << "Order Number: " << catalog[i].orderNum << std::endl;
			std::cout << "Name: " << catalog[i].name << std::endl;
			std::cout << "Release Date: " << catalog[i].releaseDate << std::endl;
			std::cout << "Price: " << catalog[i].price << std::endl;
			std::cout << "Quantity: " << catalog[i].quantity << std::endl;

			for (int j = i; j < size; j++)//readjusts array from deleted entry position
			{
				catalog[j] = catalog[j + 1];
			}

			size--;

			check = true;
		}

	}

	if (check == false)
	{
		std::cout << "No such entry" << del << std::endl;
	}

	return size;
}