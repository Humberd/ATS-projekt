#pragma once
#include <string>
#include <ostream>
#include "Printable.h"

using namespace std;

class LexerToken: public Printable {
private:
	string key;
	string value;
	int fileLineNumber;

public:
	explicit LexerToken(string key, string value, int fileLineNumber);
	explicit LexerToken(string key, char value, int fileLineNumber);
	explicit LexerToken(char key, char value, int fileLineNumber);
	explicit LexerToken(char key, string value, int fileLineNumber);
	~LexerToken();

	string getKey() const;
	string getValue() const;
	int getFileLineNumber() const;

	bool isKeyword() const;
	bool isName() const;
	bool isInteger() const;
	bool isOperator() const;
	bool isSpecialCharacter() const;

	bool isProcedure() const;
	bool isWhile() const;
	bool isIf() const;
	bool isElse() const;
	bool isCall() const;
	bool isThen() const;

	bool isPlus() const;
	bool isMinus() const;
	bool isTimes() const;

	bool isOpenBrace() const;
	bool isCloseBrace() const;
	bool isEquals() const;
	bool isSemicolon() const;


	string toString() const override;
};
