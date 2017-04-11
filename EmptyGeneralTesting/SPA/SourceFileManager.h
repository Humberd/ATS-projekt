#pragma once
#include <stddef.h>
#include <string>
#include <fstream>

using namespace std;

class SourceFileManager {
private:
	string filePath;
	ifstream inputStream;

	void openFile();
	void closeFile();

public:
	explicit SourceFileManager(string filePath);
	~SourceFileManager();

	void readFile();
};