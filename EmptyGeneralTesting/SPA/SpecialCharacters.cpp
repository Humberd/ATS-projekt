#include "SpecialCharacters.h"

SpecialCharacters::SpecialCharacters() {
}

SpecialCharacters::~SpecialCharacters() {
}

const string SpecialCharacters::OPEN_BRACE = "{";
const string SpecialCharacters::CLOSE_BRACE = "}";
const string SpecialCharacters::EQUALS_SIGN = "=";
const string SpecialCharacters::PLUS_SIGN = "+";
const string SpecialCharacters::MINUS_SIGN = "-";
const string SpecialCharacters::TIMES_SIGN = "-";
const string SpecialCharacters::SEMICOLON = ";";

string SpecialCharacters::getAll() {
	return OPEN_BRACE +
			CLOSE_BRACE +
			EQUALS_SIGN +
			PLUS_SIGN +
			MINUS_SIGN +
			TIMES_SIGN +
			SEMICOLON;
}
