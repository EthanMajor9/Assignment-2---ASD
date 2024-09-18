// Assignment 2 - ASD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


#define STUDENT_DATA_FILENAME "StudentData.txt"
#define STUDENT_DATA_EMAILS_FILENAME "StudentData_Emails.txt"
#define DATA_DELIMITER ','

struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
};

std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename);
STUDENT_DATA ParseFirstAndLastName(std::string lineToParse);

int main()
{
	std::vector<STUDENT_DATA> completeStudentData = ParseDataFile(STUDENT_DATA_FILENAME);

#ifdef _DEBUG
	for (int i = 0; i < completeStudentData.size(); i++) {
		std::cout << completeStudentData[i].firstName << " " << completeStudentData[i].lastName << std::endl;
	}
#endif

	return 1;
}


std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename) {
	std::ifstream dataFile;
	std::vector<STUDENT_DATA> completeStudentData;

	// Open data file
	dataFile.open(dataFilename);

	if (dataFile.is_open()) {
		// Read file line by line until EOF
		while (dataFile) {
			std::string line;
			std::getline(dataFile, line);

			// Construct student object with parsed information
			STUDENT_DATA newStudentData = ParseFirstAndLastName(line);
			if (newStudentData.firstName == "") break;
			completeStudentData.push_back(newStudentData);
		}
	}

	return completeStudentData;
}


STUDENT_DATA ParseFirstAndLastName(std::string lineToParse) {
	STUDENT_DATA newStudentData;

	if (lineToParse == "") return newStudentData;

	// Extract name and last name from line read from file
	int pos = lineToParse.find(DATA_DELIMITER);
	newStudentData.firstName = lineToParse.substr(pos + 2);
	newStudentData.lastName = lineToParse.substr(0, pos);

	return newStudentData;
}
