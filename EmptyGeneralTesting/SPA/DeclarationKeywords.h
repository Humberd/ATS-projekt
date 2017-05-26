#pragma once

#include <string>

using namespace std;

class DeclarationKeywords {
private:
	DeclarationKeywords();
	~DeclarationKeywords();

public:
	static const string WHILE;
	static const string IF;
	static const string ASSIGN;
	static const string CALL;
	static const string STATEMENT;
	static const string VARIABLE;
	static const string PROCEDURE;
	static const string CONSTANT;

	static bool isDeclarationKeyword(string value);
};