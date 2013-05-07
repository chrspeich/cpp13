#include "Functions.h"
#include <iostream>

// the main function
int main(int numArguments, char** arguments)
{
	try
{
    // code that could cause exception

	if(numArguments != 2)
	{
		std::cerr << "Expected filename as first argument!";
		return 1;
	}

	// read file
	std::cout << "Reading file \"" << arguments[1] << "\"." << std::endl;
	std::string fileAsString = readFileToString(arguments[1]);
	if(fileAsString.empty())
	{
		std::cerr << "Error reading file!\n" << std::endl;
		return 1;
	}

	// break down into items
	Table table = itemArrayFromCSV(fileAsString);
		
	// print table
	std::cout << std::endl;
	printTable(table);

}
catch (const std::exception &exc)
{
    // catch anything thrown within try block that derives from std::exception
    std::cerr << exc.what();
}
	return 0;
}