#include "LexerToken.h"

LexerToken::LexerToken(string key, string value): key(key), value(value) {
}

LexerToken::LexerToken(string key, char value): LexerToken(key, string(1, value)) {
}

LexerToken::LexerToken(char key, char value): LexerToken(string(1, key), string(1, value)) {
}

LexerToken::LexerToken(char key, string value): LexerToken(string(1, key), value) {
}

LexerToken::~LexerToken() {
}

string LexerToken::getKey() const {
	return key;
}

string LexerToken::getValue() const {
	return value;
}
