#pragma once
#include <fstream>
#include <vector>

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

	vector<string> readFile();
};