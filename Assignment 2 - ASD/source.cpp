// Assignment 2 - ASD.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

//#define PRE_RELEASE

#define STUDENT_DATA_FILENAME "StudentData.txt"
#define STUDENT_DATA_EMAILS_FILENAME "StudentData_Emails.txt"
#define DATA_DELIMITER ','

struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
	std::string email;
};

std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename);
STUDENT_DATA ParseFirstAndLastName(std::string lineToParse);
void PrintStudentData(std::vector<STUDENT_DATA> studentData);

int main()
{
	std::vector<STUDENT_DATA> completeStudentData;

#ifdef PRE_RELEASE
	std::cout << "Program running in PreRelease mode" << std::endl << std::endl;
	completeStudentData = ParseDataFile(STUDENT_DATA_EMAILS_FILENAME);
#else
	std::cout << "Program running in Standard mode" << std::endl << std::endl ;
	completeStudentData = ParseDataFile(STUDENT_DATA_FILENAME);
#endif

#ifdef _DEBUG
	PrintStudentData(completeStudentData);
#endif

	return 1;
}


std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename) {
	std::ifstream dataFile;
	std::vector<STUDENT_DATA> completeStudentData;

	// Open data file
	dataFile.open(dataFilename);

	if (!dataFile.is_open()) {
		std::cerr << "Error opening file: " << dataFilename << std::endl;
		return completeStudentData;
	}

	// Read file line by line until EOF
	std::string line;
	while (dataFile) {
		std::getline(dataFile, line);

		// Construct student object with parsed information
		STUDENT_DATA newStudentData = ParseFirstAndLastName(line);
		if (newStudentData.firstName.empty()) break;
		completeStudentData.push_back(newStudentData);
	}

	return completeStudentData;
}


STUDENT_DATA ParseFirstAndLastName(std::string lineToParse) {
	STUDENT_DATA newStudentData;

	if (lineToParse.empty()) return newStudentData;
	
	std::stringstream stringStream(lineToParse);
	std::vector<std::string> dataFields;
	std::string field;

	while (std::getline(stringStream, field, DATA_DELIMITER)) {
		dataFields.push_back(field);
	}

	newStudentData.firstName = dataFields[1];
	newStudentData.lastName = dataFields[0];

	if (dataFields.size() > 2)
		newStudentData.email = dataFields[2];

	return newStudentData;
}


void PrintStudentData(std::vector<STUDENT_DATA> studentData) {
	for (int i = 0; i < studentData.size(); i++) {
		std::cout << studentData[i].firstName << '\t' << studentData[i].lastName;
		if (studentData[i].email != "") {
			std::cout << '\t' << studentData[i].email << std::endl;
		}
		else { std::cout << std::endl; }
	}
}