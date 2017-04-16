#pragma once
#include <string>

using namespace std;

class LexerToken {
private:
	string key;
	string value;
	int fileLineNumber;

public:
	explicit LexerToken(string key, string value, int fileLineNumber);
	explicit LexerToken(string key, char value, int fileLineNumber);
	explicit LexerToken(char key, char value, int fileLineNumber);
	explicit LexerToken(char key, string value, int fileLineNumber);
	~LexerToken();

	string getKey() const;
	string getValue() const;
	int getFileLineNumber() const;
};
