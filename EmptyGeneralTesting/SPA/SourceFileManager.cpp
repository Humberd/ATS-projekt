#include "SourceFileManager.h"
#include "SourceFileException.h"
#include <CppUnitTestLogger.h>

SourceFileManager::SourceFileManager(string filePath) : filePath(filePath) {
	this->openFile();
}

SourceFileManager::~SourceFileManager() {
	this->closeFile();
}

void SourceFileManager::openFile() {
	inputStream.open(this->filePath);
}

void SourceFileManager::closeFile() {
	inputStream.close();
}

void SourceFileManager::readFile() {
	if (!inputStream.is_open()) {
		throw SourceFileException("Cannot open a file: " + this->filePath);
	}

	for (string str; getline(this->inputStream, str);) {
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(str.c_str());
	}
}
