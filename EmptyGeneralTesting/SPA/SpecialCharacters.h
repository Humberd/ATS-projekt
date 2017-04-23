#pragma once
#include <string>

using namespace std;

class SpecialCharacters {
private:
	SpecialCharacters();
	~SpecialCharacters();

public:
	static const string OPEN_BRACE;
	static const string CLOSE_BRACE;
	static const string EQUALS_SIGN;
	static const string SEMICOLON;

	static bool isSpecialCharacter(string value);
	static bool isSpecialCharacter(char value);
};
