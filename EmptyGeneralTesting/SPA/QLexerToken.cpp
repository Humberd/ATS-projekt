#include "QLexerToken.h";
#include "QTokenKeys.h"
#include "DeclarationKeywords.h"
#include "QueryKeywords.h"
#include "QueryMethods.h"
#include "QuerySpecialCharacters.h"

QLexerToken::QLexerToken(string key, string value): key(key), value(value) {
}


QLexerToken::QLexerToken(string key, char value): QLexerToken(key, string(1, value)) {
}

QLexerToken::~QLexerToken() {
}

string QLexerToken::getKey() const {
	return key;
}

string QLexerToken::getValue() const {
	return value;
}

bool QLexerToken::isDeclarationKeyword() const {
	return key == QTokenKeys::DECLARATION_KEYWORD;
}

bool QLexerToken::isQueryKeyword() const {
	return key == QTokenKeys::QUERY_KEYWORD;
}

bool QLexerToken::isQueryMethod() const {
	return key == QTokenKeys::QUERY_METHOD;
}

bool QLexerToken::isName() const {
	return key == QTokenKeys::NAME;
}

bool QLexerToken::isInteger() const {
	return key == QTokenKeys::INTEGER;
}

bool QLexerToken::isSpecialCharacter() const {
	return key == QTokenKeys::SPECIAL_CHARACTER;
}

bool QLexerToken::isWhileType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::WHILE;
}

bool QLexerToken::isIfType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::IF;
}

bool QLexerToken::isAssignType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::ASSIGN;
}

bool QLexerToken::isCallType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::CALL;
}

bool QLexerToken::isStatementType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::STATEMENT;
}

bool QLexerToken::isVariableType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::VARIABLE;
}

bool QLexerToken::isProcedureType() const {
	return isDeclarationKeyword() && value == DeclarationKeywords::PROCEDURE;
}

bool QLexerToken::isSelect() const {
	return isQueryKeyword() && value == QueryKeywords::SELECT;
}

bool QLexerToken::isSuch() const {
	return isQueryKeyword() && value == QueryKeywords::SUCH;
}

bool QLexerToken::isThat() const {
	return isQueryKeyword() && value == QueryKeywords::THAT;
}

bool QLexerToken::isAnd() const {
	return isQueryKeyword() && value == QueryKeywords::AND;
}

bool QLexerToken::isBoolean() const {
	return isQueryKeyword() && value == QueryKeywords::BOOLEAN;
}

bool QLexerToken::isParentMethod() const {
	return isQueryMethod() && value == QueryMethods::PARENT;
}

bool QLexerToken::isFollowsMethod() const {
	return isQueryMethod() && value == QueryMethods::FOLLOWS;
}

bool QLexerToken::isUsesMethod() const {
	return isQueryMethod() && value == QueryMethods::USES;
}

bool QLexerToken::isCallsMethod() const {
	return isQueryMethod() && value == QueryMethods::CALLS;
}

bool QLexerToken::isNextMethod() const {
	return isQueryMethod() && value == QueryMethods::NEXT;
}

bool QLexerToken::isModifiesMethod() const {
	return isQueryMethod() && value == QueryMethods::MODIFIES;
}

bool QLexerToken::isAffectsMethod() const {
	return isQueryMethod() && value == QueryMethods::AFFECTS;
}

bool QLexerToken::isPatternMethod() const {
	return isQueryMethod() && value == QueryMethods::PATTERN;
}

bool QLexerToken::isStar() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::STAR;
}

bool QLexerToken::isComma() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::COMMA;
}

bool QLexerToken::isSemicolon() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::SEMICOLON;
}

bool QLexerToken::isOpenBrace() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::OPENBRACE;
}

bool QLexerToken::isCloseBrace() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::CLOSEBRACE;
}

bool QLexerToken::isQuotationMark() const {
	return isSpecialCharacter() && value == QuerySpecialCharacters::QUOTATIONMARK;
}

string QLexerToken::toString() const {
	return "{key: '" + key + "', value: '" + value + "}";
}
