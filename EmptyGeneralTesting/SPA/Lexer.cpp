#include "Lexer.h"
#include <cctype>
#include "SpecialCharacters.h"
#include <CppUnitTestLogger.h>

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
		} else if (isIn(character, SpecialCharacters::getAll())) {
			result.push_back(new LexerToken("specialCharacter", character));
		} else if (std::isalpha(character)) {
			result.push_back(new LexerToken("name", scanName(&iterator, &sourceLine.end())));
		} else if (std::isdigit(character)) {
			result.push_back(new LexerToken("integer", scanName(&iterator, &sourceLine.end())));
		} else {
			throw exception("Unknown symbol: " + character);
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


string Lexer::scanName(string::iterator* iterator, string::iterator* endIterator) {
	auto normalIterator = **(&iterator);
	auto normalEndIterator = **(&endIterator);

	/*The first letter is already known to be an alpha*/
	string response = "";
	response += *normalIterator;

	while (true) {
		if (normalIterator == normalEndIterator) {
			break;
		}
		++normalIterator;

//		auto character = *normalIterator;
//
//		if (std::isalnum(character)) {
//			response += character;
//		} else if (std::isblank(character)) {
//			break;
//		} else {
//			throw exception("Unknown character in scanning a name: " + character);
//		}
	}

	//	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage()

	return response;
}

string Lexer::scanInteger(string::iterator* iterator, string::iterator* endIterator) {
	return "foo";
}
