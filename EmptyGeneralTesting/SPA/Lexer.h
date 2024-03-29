#pragma once
#include <vector>
#include "LexerToken.h"

using namespace std;

class Lexer {
private:
	Lexer();

public:
	~Lexer();

	static vector<LexerToken*> parse(vector<string>& sourceLines);
	static vector<LexerToken*> parseLine(string sourceLine, int sourceLineNumber);

	static void mergeVectors(vector<LexerToken*>& to, vector<LexerToken*>& add);
	static string scanName(string::iterator& iterator, string::iterator& endIterator);
	static string scanInteger(string::iterator& iterator, string::iterator& endIterator);
};