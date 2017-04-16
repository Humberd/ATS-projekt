#include "LexerToken.h"
#include "TokenKeys.h"
#include "Keywords.h"
#include "Operators.h"
#include "SpecialCharacters.h"

LexerToken::LexerToken(string key, string value, int fileLineNumber): key(key), value(value), fileLineNumber(fileLineNumber) {
}

LexerToken::LexerToken(string key, char value, int fileLineNumber): LexerToken(key, string(1, value), fileLineNumber) {
}

LexerToken::LexerToken(char key, char value, int fileLineNumber): LexerToken(string(1, key), string(1, value), fileLineNumber) {
}

LexerToken::LexerToken(char key, string value, int fileLineNumber): LexerToken(string(1, key), value, fileLineNumber) {
}

LexerToken::~LexerToken() {
}

string LexerToken::getKey() const {
	return key;
}

string LexerToken::getValue() const {
	return value;
}

int LexerToken::getFileLineNumber() const {
	return fileLineNumber;
}

bool LexerToken::isKeyword() const {
	return key == TokenKeys::KEYWORD;
}

bool LexerToken::isName() const {
	return key == TokenKeys::NAME;
}

bool LexerToken::isInteger() const {
	return key == TokenKeys::INTEGER;
}

bool LexerToken::isOperator() const {
	return key == TokenKeys::OPERATOR;
}

bool LexerToken::isSpecialCharacter() const {
	return key == TokenKeys::SPECIAL_CHARACTER;
}

bool LexerToken::isProcedure() const {
	return isKeyword() && value == Keywords::PROCEDURE;
}

bool LexerToken::isWhile() const {
	return isKeyword() && value == Keywords::WHILE;
}

bool LexerToken::isIf() const {
	return isKeyword() && value == Keywords::IF;
}

bool LexerToken::isElse() const {
	return isKeyword() && value == Keywords::ELSE;
}

bool LexerToken::isCall() const {
	return isKeyword() && value == Keywords::CALL;
}

bool LexerToken::isThen() const {
	return isKeyword() && value == Keywords::THEN;
}


bool LexerToken::isPlus() const {
	return isOperator() && value == Operators::PLUS_SIGN;
}

bool LexerToken::isMinus() const {
	return isOperator() && value == Operators::MINUS_SIGN;
}

bool LexerToken::isTimes() const {
	return isOperator() && value == Operators::TIMES_SIGN;
}


bool LexerToken::isOpenBrace() const {
	return isSpecialCharacter() && value == SpecialCharacters::OPEN_BRACE;
}

bool LexerToken::isCloseBrace() const {
	return isSpecialCharacter() && value == SpecialCharacters::CLOSE_BRACE;
}

bool LexerToken::isEquals() const {
	return isSpecialCharacter() && value == SpecialCharacters::EQUALS_SIGN;
}

bool LexerToken::isSemicolon() const {
	return isSpecialCharacter() && value == SpecialCharacters::SEMICOLON;
}


string LexerToken::toString() const {
	return "{key: '" + key + "', value: '" + value + "', fileLineNumber: '" + to_string(fileLineNumber) + "'}";
}
