#pragma once
#include <string>

using namespace std;

class QLexerToken {
private:
	string key;
	string value;

public:
	explicit QLexerToken(string key, string value);
	explicit QLexerToken(string key, char value);
	~QLexerToken();

	string getKey() const;
	string getValue() const;

	bool isDeclarationKeyword() const;
	bool isQueryKeyword() const;
	bool isQueryMethod() const;
	bool isName() const;
	bool isInteger() const;
	bool isSpecialCharacter() const;

	bool isWhileType() const;
	bool isIfType() const;
	bool isAssignType() const;
	bool isCallType() const;
	bool isStatementType() const;
	bool isVariableType() const;
	bool isProcedureType() const;

	bool isSelect() const;
	bool isSuch() const;
	bool isThat() const;
	bool isAnd() const;
	bool isBoolean() const;

	bool isParentMethod() const;
	bool isFollowsMethod() const;
	bool isUsesMethod() const;
	bool isCallsMethod() const;
	bool isNextMethod() const;
	bool isModifiesMethod() const;
	bool isAffectsMethod() const;
	bool isPatternMethod() const;

	bool isStar() const;
	bool isComma() const;
	bool isSemicolon() const;
	bool isOpenBrace() const;
	bool isCloseBrace() const;
	bool isQuotationMark() const;

	string toString() const;
};
