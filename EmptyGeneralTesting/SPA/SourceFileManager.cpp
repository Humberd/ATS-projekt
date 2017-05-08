#include "SourceFileManager.h"
#include "SourceFileException.h"
//#include <CppUnitTestLogger.h>
#include <numeric>

SourceFileManager::SourceFileManager(string filePath) : filePath(filePath) {
	this->openFile();
}

SourceFileManager::~SourceFileManager() {
	this->closeFile();
}

void SourceFileManager::openFile() {
	inputStream.open(filePath);
}

void SourceFileManager::closeFile() {
	inputStream.close();
}

vector<string> SourceFileManager::readFile() {
	vector<string> result;

	if (!inputStream.is_open()) {
		throw SourceFileException("Cannot open a file: " + filePath);
	}

	/*Read line by line*/
	for (string str; getline(inputStream, str);) {
		/*If after reading there is an error*/
		if (inputStream.fail()) {
			string whatIManagedToRead;
			whatIManagedToRead = accumulate(begin(result), end(result), whatIManagedToRead);
			throw SourceFileException("There was a problem reading a file: " + filePath + " | " + whatIManagedToRead);
		}
		result.push_back(str);
	}

	return result;
}
