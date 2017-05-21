#pragma once
#include <string>

using namespace std;

class QuerySpecialCharacters {
private:
	QuerySpecialCharacters();
	~QuerySpecialCharacters();

public:
	static const string STAR; // *
	static const string COMMA; // ,
	static const string SEMICOLON; // ;
	static const string OPENBRACE; // (
	static const string CLOSEBRACE; // )
	static const string QUOTATIONMARK; // "
	static const string DIAMONBRACEOPEN; // <
	static const string DIAMONDBRACECLOSE; // >
	static const string LOWDASH; // _

	static bool isQuerySpecialCharacter(string value);
	static bool isQuerySpecialCharacter(char value);
};