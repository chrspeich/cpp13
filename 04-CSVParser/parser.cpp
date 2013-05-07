#include "Functions.h"

#include <fstream>
#include <regex>
#include <iostream>

using namespace std;

std::string readFileToString(const std::string& filename)
{
	ifstream file;

	file.open(filename, ios::in | ios::binary);
	
	if (file.is_open()) {
		string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		return content;
	}

	return "";
}

Table itemArrayFromCSV(const std::string& csv)
{
	Table table;
	vector<string> entry;

	regex e("(?:(?:[^\\n\\\";]+|\\\"([^\\\"]*)\\\")+|\\n)");

	auto iter = sregex_iterator( csv.begin(), csv.end(), e, regex_constants::match_any);
  	auto iter_end = sregex_iterator();

  	while (iter!=iter_end) {
  		if (iter->str() == "\n") {
  			table.push_back(entry);
  			entry = vector<string>();
  		}
  		else {
  			auto str = (*iter)[1].str();
  			if (str.empty())
  				str = (*iter)[0].str();

    		entry.push_back(str);
    	}
    	
    	++iter;
	}

	if (!entry.empty()) {
		table.push_back(entry);
	}

	return table;
}

void printTable(const Table& table)
{
	for (const vector<string> &row : table) {
    	for (const string &str: row) {
    		std::cout.width (25);
    		cout << str;
    	}
    	cout << endl;
	}
}