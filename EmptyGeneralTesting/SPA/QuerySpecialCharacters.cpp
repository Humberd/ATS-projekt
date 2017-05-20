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

bool QuerySpecialCharacters::isQuerySpecialCharacter(string value) {
	return value == STAR ||
			value == COMMA ||
			value == SEMICOLON ||
			value == OPENBRACE ||
			value == CLOSEBRACE ||
			value == QUOTATIONMARK;
}
