#include "Keywords.h"

Keywords::Keywords() {
}

Keywords::~Keywords() {
}

const string Keywords::PROCEDURE = "procedure";
const string Keywords::WHILE = "while";
const string Keywords::IF = "if";
const string Keywords::THEN = "then";
const string Keywords::ELSE = "else";
const string Keywords::CALL = "call";


bool Keywords::isKeyword(string value) {
	return value == PROCEDURE ||
			value == WHILE ||
			value == IF ||
			value == THEN ||
			value == ELSE ||
			value == CALL;
}
