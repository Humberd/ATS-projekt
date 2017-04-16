#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/Node.h"
#include "../SPA/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ParserTest) {
	TEST_METHOD(Parser_parse_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken("keyword", "procedure", 1));
		tokensList.push_back(new LexerToken("name", "MyProc", 1));
		tokensList.push_back(new LexerToken("specialcharacter", "{", 1));

		tokensList.push_back(new LexerToken("name", "x", 2));
		tokensList.push_back(new LexerToken("specialcharacter", "=", 2));
		tokensList.push_back(new LexerToken("integer", "2", 2));
		tokensList.push_back(new LexerToken("specialcharacter", ";", 2));
		tokensList.push_back(new LexerToken("specialcharacter", "}", 2));

		Node* rootNode = Parser::parse(tokensList);

		for (auto token : tokensList) {
			delete token;
		}

		tokensList.clear();
		delete rootNode;
	}
};
