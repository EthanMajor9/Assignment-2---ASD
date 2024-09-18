/*
* FILE:			  source.cpp
* PROJECT:		  Assignment 2
* FIRST VERSION:  2024 - 09 - 18
* PROGRAMMER(s):  Ethan Major
* DESCRIPTION:    This file contains all of the logic for Assignment 2 of Project V: Advanced Software Development
*/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define PRE_RELEASE

#define STUDENT_DATA_FILENAME "StudentData.txt"
#define STUDENT_DATA_EMAILS_FILENAME "StudentData_Emails.txt"
#define DATA_DELIMITER ','

// Struct to store student data
struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
	std::string email;
};

// Prototypes
std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename);
STUDENT_DATA ParseFirstAndLastName(std::string lineToParse);
void PrintStudentData(std::vector<STUDENT_DATA> studentData);

int main()
{
	std::vector<STUDENT_DATA> completeStudentData;


//  PreRelease Compiler directive logic
#ifdef PRE_RELEASE
	std::cout << "Program running in PreRelease mode" << std::endl << std::endl;
	completeStudentData = ParseDataFile(STUDENT_DATA_EMAILS_FILENAME);
#else
	std::cout << "Program running in Standard mode" << std::endl << std::endl ;
	completeStudentData = ParseDataFile(STUDENT_DATA_FILENAME);
#endif

// Debug/Release compiler directive logic
#ifdef _DEBUG
	PrintStudentData(completeStudentData);
#endif

	return 1;
}


// METHOD:      std::vector<STUDENT_DATA> ParseDataFile(std::string dataFilename)
// DESCRIPTION: Reads line by line from a data file and creates STUDENT_DATA objects filled with the information read.
// PARAMETERS:  
//   std::string dataFileName - Name of the data file to read from
// RETURNS:		
//   std::vector<STUDENT_DATA> - Returns a vector containing structs of student data parsed from the data file
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


// METHOD:      STUDENT_DATA ParseFirstAndLastName(std::string lineToParse)
// DESCRIPTION: Parses the student fields from the line passed in based on the ',' delimiter and constructs a STUDEN_DATA object
// PARAMETERS:  
//	 std::string lineToParse - Full line read from the file to parse student data from
// RETURNS:		
//   struct STUDENT_DATA - Newly created student data object populated with the fields read from the line passed in as an argument
STUDENT_DATA ParseFirstAndLastName(std::string lineToParse) {
	STUDENT_DATA newStudentData;

	if (lineToParse.empty()) return newStudentData;
	
	std::stringstream stringStream(lineToParse);
	std::vector<std::string> dataFields;
	std::string field;

	// Split the string on every instance of the delimiter
	while (std::getline(stringStream, field, DATA_DELIMITER)) {
		dataFields.push_back(field);
	}

	// Fill student_data object
	newStudentData.firstName = dataFields[1];
	newStudentData.lastName = dataFields[0];

	if (dataFields.size() > 2)
		newStudentData.email = dataFields[2];

	return newStudentData;
}


// METHOD:      void PrintStudentData(std::vector<STUDENT_DATA> studentData)
// DESCRIPTION: This function iterates through all of the student data and outputs it to the console
// PARAMETERS:  
//	  std::vector<STUDENT_DATA> - Vector populated with full structs of student data parsed from the data file
// RETURNS:		None
void PrintStudentData(std::vector<STUDENT_DATA> studentData) {
	for (int i = 0; i < studentData.size(); i++) {
		std::cout << studentData[i].firstName << '\t' << studentData[i].lastName;
		if (studentData[i].email != "") {
			std::cout << '\t' << studentData[i].email << std::endl;
		}
		else { std::cout << std::endl; }
	}
}