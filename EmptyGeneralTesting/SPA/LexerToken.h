#pragma once
#include <string>

using namespace std;

class LexerToken {
private:
	string key;
	string value;

public:
	explicit LexerToken(string key, string value);
	explicit LexerToken(string key, char value);
	explicit LexerToken(char key, char value);
	explicit LexerToken(char key, string value);
	~LexerToken();


	string getKey() const;
	string getValue() const;
};
