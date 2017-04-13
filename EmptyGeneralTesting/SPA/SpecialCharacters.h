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
	static const string PLUS_SIGN;
	static const string MINUS_SIGN;
	static const string TIMES_SIGN;
	static const string SEMICOLON;
};
