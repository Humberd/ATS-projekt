#include "SpecialCharacters.h"

SpecialCharacters::SpecialCharacters() {
}

SpecialCharacters::~SpecialCharacters() {
}

const string SpecialCharacters::OPEN_BRACE = "{";
const string SpecialCharacters::CLOSE_BRACE = "}";
const string SpecialCharacters::EQUALS_SIGN = "=";
const string SpecialCharacters::SEMICOLON = ";";

bool SpecialCharacters::isSpecialCharacter(string value) {
	return value == OPEN_BRACE ||
			value == CLOSE_BRACE ||
			value == EQUALS_SIGN ||
			value == SEMICOLON;
}


bool SpecialCharacters::isSpecialCharacter(char value) {
	return isSpecialCharacter(string(1, value));
}
