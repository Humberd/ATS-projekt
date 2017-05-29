#include "DeclarationKeywords.h"

DeclarationKeywords::DeclarationKeywords() {
}

DeclarationKeywords::~DeclarationKeywords() {
}

const string DeclarationKeywords::WHILE = "while";
const string DeclarationKeywords::IF = "if";
const string DeclarationKeywords::ASSIGN = "assign";
const string DeclarationKeywords::CALL = "call";
const string DeclarationKeywords::STATEMENT = "stmt";
const string DeclarationKeywords::VARIABLE = "variable";
const string DeclarationKeywords::PROCEDURE = "procedure";
const string DeclarationKeywords::CONSTANT = "constant";

bool DeclarationKeywords::isDeclarationKeyword(string value) {
	return value == WHILE ||
			value == IF ||
			value == ASSIGN ||
			value == CALL ||
			value == STATEMENT ||
			value == VARIABLE ||
			value == PROCEDURE ||
			value == CONSTANT;
}
