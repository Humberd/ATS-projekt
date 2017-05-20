#include "QLexer.h"
#include <cctype>
#include "QLexerException.h"
#include "QuerySpecialCharacters.h"
#include "QTokenKeys.h"
#include <locale>
#include "DeclarationKeywords.h"
#include "QueryKeywords.h"
#include "QueryMethods.h"

QLexer::QLexer() {
}

QLexer::~QLexer() {
}

/*
 * Declarations don't allow solo integers (can be allowed in a variable name),
 * so I don't even check them; just throws an exception.
 */
vector<QLexerToken*> QLexer::parseDeclarations(string sourceDeclarations) {
	vector<QLexerToken*> result;

	auto iterator = sourceDeclarations.begin();
	auto iteratorEnd = sourceDeclarations.end();

	while (iterator != iteratorEnd) {
		auto character = *iterator;

		/*If a character is a space or a tab*/
		if (std::isblank(character)) {
			++iterator;
			continue;
		}
		/*If a character is a special character: '*,;()\"' */
		else if (QuerySpecialCharacters::isQuerySpecialCharacter(character)) {
			result.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, character));
			++iterator;
		}
		/*If a character is alphanumeric:
		* Start with: a-zA-Z
		* All next: a-zA-Z0-9
		*/
		else if (isalpha(character)) {
			string name = scanName(iterator, iteratorEnd);

			if (DeclarationKeywords::isDeclarationKeyword(name)) {
				result.push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, name));
			} else {
				result.push_back(new QLexerToken(QTokenKeys::NAME, name));
			}
		}
		/*If I can't find an appropriate symbol*/
		else {
			throw QLexerException("Unknown symbol: " + character);
		}
	}

	return result;
}

vector<QLexerToken*> QLexer::parseQuery(string sourceQuery) {
	vector<QLexerToken*> result;

	auto iterator = sourceQuery.begin();
	auto iteratorEnd = sourceQuery.end();

	while (iterator != iteratorEnd) {
		auto character = *iterator;

		/*If a character is a space or a tab*/
		if (std::isblank(character)) {
			++iterator;
			continue;
		}
		/*If a character is a special character: '*,;()\"' */
		else if (QuerySpecialCharacters::isQuerySpecialCharacter(character)) {
			result.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, character));
			++iterator;
		}
		/*If a character is alphanumeric:
		* Start with: a-zA-Z
		* All next: a-zA-Z0-9
		*/
		else if (isalpha(character)) {
			string name = scanName(iterator, iteratorEnd);

			if (QueryMethods::isQueryMethod(name)) {
				result.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, name));
			} else if (QueryKeywords::isQueryKeyword(name)) {
				result.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, name));
			} else {
				result.push_back(new QLexerToken(QTokenKeys::NAME, name));
			}
		}
		/*If a character is a digit: 0-9*/
		else if (isdigit(character)) {
			result.push_back(new QLexerToken(QTokenKeys::INTEGER, scanInteger(iterator, iteratorEnd)));
		}
		/*If I can't find an appropriate symbol*/
		else {
			throw QLexerException("Unknown symbol: " + character);
		}
	}

	return result;
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
string QLexer::scanName(string::iterator& iterator, string::iterator& endIterator) {
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
				throw QLexerException("scanName - First character must be a character, but instead is: " + character);
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
			/*If there is a special character: '*,;()\"'*/
			else if (QuerySpecialCharacters::isQuerySpecialCharacter(character)) {
				break; //stop the name
			} else {
				throw QLexerException("scanName - The character of index 1 or more must be a digit or a character, but instead is: " + character);
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
string QLexer::scanInteger(string::iterator& iterator, string::iterator& endIterator) {
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
				throw QLexerException("scanInteger - First character must be a digit, but instead is: " + character);
			}
		}
		/*If the integer has been started*/
		else if (response.length() != 0) {
			/*If there is a space or a tab*/
			if (std::isblank(character)) {
				break; //stop the integer
			}
			/*If there is a special character: '*,;()\"'*/
			else if (QuerySpecialCharacters::isQuerySpecialCharacter(character)) {
				break; //stop the integer
			} else {
				throw QLexerException("scanInteger - The character of index 1 or more must be a digit, but isntead is: " + character);
			}
		}
	}
	return response;
}

string QLexer::scanAlnum(string::iterator& iterator, string::iterator& endIterator) {
	return nullptr;
}

string QLexer::scanString(string::iterator& iterator, string::iterator& endIterator) {
	return nullptr;
}
