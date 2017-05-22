#include "QuerySpecialCharacters.h"

QuerySpecialCharacters::QuerySpecialCharacters() {
}

QuerySpecialCharacters::~QuerySpecialCharacters() {
}

const string QuerySpecialCharacters::STAR = "*";
const string QuerySpecialCharacters::COMMA = ",";
const string QuerySpecialCharacters::SEMICOLON = ";";
const string QuerySpecialCharacters::OPENBRACE = "(";
const string QuerySpecialCharacters::CLOSEBRACE = ")";
const string QuerySpecialCharacters::QUOTATIONMARK = "\"";
const string QuerySpecialCharacters::DIAMONBRACEOPEN = "<";
const string QuerySpecialCharacters::DIAMONDBRACECLOSE = ">";
const string QuerySpecialCharacters::LOWDASH = "_";
const string QuerySpecialCharacters::DOT = ".";
const string QuerySpecialCharacters::HASH = "#";
const string QuerySpecialCharacters::EQUALS = "=";

bool QuerySpecialCharacters::isQuerySpecialCharacter(string value) {
	return value == STAR ||
			value == COMMA ||
			value == SEMICOLON ||
			value == OPENBRACE ||
			value == CLOSEBRACE ||
			value == QUOTATIONMARK ||
			value == DIAMONBRACEOPEN ||
			value == DIAMONDBRACECLOSE ||
			value == LOWDASH ||
			value == DOT ||
			value == HASH ||
			value == EQUALS;
}

bool QuerySpecialCharacters::isQuerySpecialCharacter(char value) {
	return isQuerySpecialCharacter(string(1, value));
}
