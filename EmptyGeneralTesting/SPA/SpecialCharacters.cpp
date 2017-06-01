#include "SpecialCharacters.h"

SpecialCharacters::SpecialCharacters() {
}

SpecialCharacters::~SpecialCharacters() {
}

const string SpecialCharacters::OPEN_BRACE = "{";
const string SpecialCharacters::CLOSE_BRACE = "}";
const string SpecialCharacters::EQUALS_SIGN = "=";
const string SpecialCharacters::SEMICOLON = ";";
const string SpecialCharacters::PARENTHASIS_OPEN = "(";
const string SpecialCharacters::PARENTHASIS_CLOSE = ")";

bool SpecialCharacters::isSpecialCharacter(string value) {
	return value == OPEN_BRACE ||
			value == CLOSE_BRACE ||
			value == EQUALS_SIGN ||
			value == SEMICOLON ||
			value == PARENTHASIS_OPEN ||
			value == PARENTHASIS_CLOSE;
}


bool SpecialCharacters::isSpecialCharacter(char value) {
	return isSpecialCharacter(string(1, value));
}
