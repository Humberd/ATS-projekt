#include "Lexer.h"
#include <cctype>
#include "SpecialCharacters.h"
#include <CppUnitTestLogger.h>
#include "LexerException.h"

Lexer::Lexer() {
}

Lexer::~Lexer() {
}

vector<LexerToken*> Lexer::parse(vector<string> sourceLines) {
	vector<LexerToken*> result;

	for (auto line : sourceLines) {
		auto parsedLine = parseLine(line);
		mergeVectors(&result, &parsedLine);
	}

	return result;
}


vector<LexerToken*> Lexer::parseLine(string sourceLine) {
	vector<LexerToken*> result;

	auto iterator = sourceLine.begin();

	while (iterator != sourceLine.end()) {
		auto character = *iterator;

		if (std::isblank(character)) {
			continue;
		} else if (isIn(character, "{}=;")) {
			result.push_back(new LexerToken("specialCharacter", character));
		} else if (isIn(character, "+-*")) {
			result.push_back(new LexerToken("operation", character));
		} else if (std::isalpha(character)) {
			result.push_back(new LexerToken("name", scanName(iterator, sourceLine.end())));
		} else if (std::isdigit(character)) {
			result.push_back(new LexerToken("integer", scanName(iterator, sourceLine.end())));
		} else {
			throw LexerException("Unknown symbol: " + character);
		}

		++iterator;
	}


	return result;
}

/*
 * Puts all the elements from second vector to the first vector
 */
void Lexer::mergeVectors(vector<LexerToken*>* to, vector<LexerToken*>* add) {
	to->reserve(to->size() + add->size());
	to->insert(to->end(), add->begin(), add->end());
}

/*
 * If a character is inside a string
 */
bool Lexer::isIn(char character, string pool) {
	return pool.find(character) != string::npos;
}

string Lexer::scanName(string::iterator& iterator, string::iterator& endIterator) {
	auto address = &iterator;
	string response = "";

	for (auto item = &iterator; *item != endIterator; ++*item) {
		/*Need to change all to lower case, because isAlpha() method works only on lowercase chars*/
		auto character = std::tolower(**item);

		/*The first character can only be a letter.
		 * Space doesn't mean anything, because the word hasn't even started yet.
		 */
		if (response.length() == 0) {
			if (std::isalpha(character)) {
				response += character;
			} else if (std::isblank(character)) {
				continue;
			} else {
				throw LexerException("First character must be a character, but instead is: " + character);
			}
		}
		/*The other characters can be either a letter or a number.
		 * The space says that the Name has ended
		 */
		else {
			if (std::isalnum(character)) {
				response += character;
			} else if (std::isblank(character)) {
				break;
			} else {
				throw LexerException("Next character must be an alphanumeric, but instead is: " + character);
			}
		}
	}
	return response;
}

string Lexer::scanInteger(string::iterator& iterator, string::iterator& endIterator) {
	string response = "";

	for (auto item = &iterator; *item != endIterator; ++*item) {
		auto character = **item;

		if (std::isdigit(character)) {
			response += character;
		} else if (std::isblank(character)) {
			/*If the number hasn't even started*/
			if (response.length() == 0)
				continue;
			/*If the number has been already started*/
			if (response.length() != 0)
				break;
		} else {
			throw LexerException("Integer can only consist of digits, but instead there is: " + character);
		}

	}
	return response;
}
