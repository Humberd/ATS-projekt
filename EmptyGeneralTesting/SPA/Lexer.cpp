#include "Lexer.h"
#include <cctype>
#include "SpecialCharacters.h"
#include "LexerException.h"
#include "Keywords.h"
#include "Operators.h"

Lexer::Lexer() {
}

Lexer::~Lexer() {
}

vector<LexerToken*> Lexer::parse(vector<string>& sourceLines) {
	vector<LexerToken*> result;
	
	for (int i = 0; i < sourceLines.size(); i++) {
		auto line = sourceLines.at(i);

		vector<LexerToken*> parsedLine = parseLine(line, i + 1);
		mergeVectors(result, parsedLine);
	}

	return result;
}


vector<LexerToken*> Lexer::parseLine(string sourceLine, int fileLineNumber) {
	vector<LexerToken*> result;

	auto iterator = sourceLine.begin();
	auto iteratorEnd = sourceLine.end();

	while (iterator != sourceLine.end()) {
		auto character = *iterator;

		/*If a character is a space or a tab*/
		if (std::isblank(character)) {
			++iterator;
			continue;
		}
		/*If a character is a special character: "{}=;" */
		else if (SpecialCharacters::isSpecialCharacter(character)) {
			result.push_back(new LexerToken("specialcharacter", character, fileLineNumber));
			++iterator;
		}
		/*If a character is an operator: "+-*" */
		else if (Operators::isOperator(character)) {
			result.push_back(new LexerToken("operator", character, fileLineNumber));
			++iterator;
		}
		/*If a character is alphanumeric:
		 * Start with: a-zA-Z
		 * All next: a-zA-Z0-9
		 */
		else if (std::isalpha(character)) {
			string name = scanName(iterator, iteratorEnd);

			if (Keywords::isKeyword(name)) {
				result.push_back(new LexerToken("keyword", name, fileLineNumber));
			} else {
				result.push_back(new LexerToken("name", name, fileLineNumber));
			}
		}
		/*If a character is a digit: 0-9*/
		else if (std::isdigit(character)) {
			result.push_back(new LexerToken("integer", scanInteger(iterator, iteratorEnd), fileLineNumber));
		}
		/*If I can't find an appropriate symbol*/
		else {
			throw LexerException("Unknown symbol: " + character);
		}
	}


	return result;
}

/*
 * Puts all the elements from second vector to the first vector
 */
void Lexer::mergeVectors(vector<LexerToken*>& to, vector<LexerToken*>& add) {
	to.reserve(to.size() + add.size());
	to.insert(to.end(), add.begin(), add.end());
}

/*
 * This method finds the first name from the string.
 * The name can have spaces before.
 * The name can end with special characters: "{}=;"
 * The name can end with operators: "+-*"
 * The name can be lowercase, UPPERCASE or MixeD
 * The name can only start with a letter, the rest can be a letter or a digit
 * " foobar" => "foobar"
 * "	foo32 " => "foo32"
 * "Foo Bar" => "Foo"
 * "foo;" => "foo"
 * "44bar" => error (name cannot start with a digit)
 * "3 bar" => error (name is not the first)
 * "foobar*9" => "foobar"
 */
string Lexer::scanName(string::iterator& iterator, string::iterator& endIterator) {
	string response = "";

	for (auto item = &iterator; *item != endIterator; ++*item) {
		auto character = **item;

		/*If the name hasn't started yet*/
		if (response.length() == 0) {
			/*If a character is alphabetic*/
			if (std::isalpha(std::tolower(character))) {
				response += character; //add to a response
			}
			/*If a character is a space or a tab before the start of the name*/
			else if (std::isblank(character)) {
				continue; //ignore
			} else {
				throw LexerException("scanName - First character must be a character, but instead is: " + character);
			}
		}
		/*If the name has been started*/
		else {
			/*If a character is alphabetic or a digit*/
			if (std::isalnum(std::tolower(character))) {
				response += character; //add to a response
			}
			/*If a character is a space or a tab*/
			else if (std::isblank(character)) {
				break; //stop the name
			}
			/*If a character is a special character: "{}=;" */
			else if (SpecialCharacters::isSpecialCharacter(character)) {
				break; //stop the name
			}
			/*If a character is an operator: "+-*" */
			else if (Operators::isOperator(character)) {
				break; //stop the name
			} else {
				throw LexerException("scanName - The character of index 1 or more must be a digit or a character, but instead is: " + character);
			}
		}
	}
	return response;
}

/*
 * This method finds the first integer from the string.
 * The integer can have spaces before.
 * The integer can end with special characters: "{}=;"
 * The integer can end with operators: "+-*"
 * " 123" => "123"
 * "  1 32" => "1"
 * "54 b3" => "54"
 * "27as 32" => error (integer cannot be concatenated with characters)
 * "23;" => "23"
 * "23{" => "23"
 * "98+12" => "98"
 * "11/32" => error ("/" is not a special character)
 * "e 32" => error (integer is not the first)
 */
string Lexer::scanInteger(string::iterator& iterator, string::iterator& endIterator) {
	string response = "";

	for (auto item = &iterator; *item != endIterator; ++*item) {
		auto character = **item;

		/*If a character is a digit*/
		if (std::isdigit(character)) {
			response += character; //add to response
		}
		/*If the integer hasn't started yet*/
		else if (response.length() == 0) {
			/*If there is a space or a tab before the start of the integer*/
			if (std::isblank(character)) {
				continue; //ignore
			} else {
				throw LexerException("scanInteger - First character must be a digit, but instead is: " + character);
			}
		}
		/*If the integer has been started*/
		else if (response.length() != 0) {
			/*If there is a space or a tab*/
			if (std::isblank(character)) {
				break; //stop the integer
			}
			/*If there is a special character: "{}=;" */
			else if (SpecialCharacters::isSpecialCharacter(character)) {
				break; //stop the integer
			}
			/*If there is an operator: "+-*" */
			else if (Operators::isOperator(character)) {
				break; //stop the integer
			} else {
				throw LexerException("scanInteger - The character of index 1 or more must be a digit, but isntead is: " + character);
			}
		}
	}
	return response;
}
