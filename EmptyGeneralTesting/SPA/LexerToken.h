#pragma once
#include <string>
#include <ostream>
#include "Printable.h"

using namespace std;

class LexerToken: public Printable {
private:
	string key;
	string value;
	int sourceLineNumber;

public:
	explicit LexerToken(string key, string value, int sourceLineNumber);
	explicit LexerToken(string key, char value, int sourceLineNumber);
	explicit LexerToken(char key, char value, int sourceLineNumber);
	explicit LexerToken(char key, string value, int sourceLineNumber);
	~LexerToken();

	string getKey() const;
	string getValue() const;
	int getSourceLineNumber() const;

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
