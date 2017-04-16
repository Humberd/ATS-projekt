#include "LexerToken.h"

LexerToken::LexerToken(string key, string value, int fileLineNumber): key(key), value(value),fileLineNumber(fileLineNumber) {
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
