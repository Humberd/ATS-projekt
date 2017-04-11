#pragma once
#include <stddef.h>
#include <string>

using namespace std;

class SourceFileManager {
private:
	string filePath;

public:
	explicit SourceFileManager(string filePath);
	~SourceFileManager();

	void readFile();
};