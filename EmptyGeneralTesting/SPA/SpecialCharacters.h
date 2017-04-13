#pragma once
#include <string>

using namespace std;

class SpecialCharacters {
private:
	SpecialCharacters();
	~SpecialCharacters();

public:
	static const char OPEN_BRACE;
	static const char CLOSE_BRACE;
	static const char EQUALS_SIGN;
	static const char PLUS_SIGN;
	static const char MINUS_SIGN;
	static const char TIMES_SIGN;
	static const char SEMICOLON;
};
