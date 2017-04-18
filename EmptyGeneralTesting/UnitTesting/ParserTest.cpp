#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/Node.h"
#include "../SPA/Parser.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/Keywords.h"
#include "../SPA/CallNode.h"

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

	TEST_METHOD(Parser_parseCall_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "FooProc", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));

		/*Check if didn't receive a nullptr*/
		Node* node = Parser::parseCall(tokensList.begin());
		Assert::IsNotNull(node);

		/*Check if Node* is a typeof CallNode* */
		CallNode* callNode = dynamic_cast<CallNode*>(node);
		Assert::IsNotNull(callNode);

		/*Ensures that callNode is valid*/
		callNode->validate();

		Assert::IsTrue(callNode->getLineNumber() == 1);
		Assert::IsTrue(callNode->getProcedureName() == "FooProc");

		for (auto token : tokensList) {
			delete token;
		}

		tokensList.clear();
		delete node;
	}

	TEST_METHOD(Parser_parseCall_Invalid) {
//		vector<vector<LexerToken*>> tokensList;
//
//		tokensList.push_back(vector<LexerToken*> );
//		tokensList.push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
//		tokensList.push_back(new LexerToken(TokenKeys::NAME, "FooProc", 1));
//		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
//
//		/*Check if didn't receive a nullptr*/
//		Node* node = Parser::parseCall(tokensList.begin(), tokensList.end());
//		Assert::IsNotNull(node);
//
//		/*Check if Node* is a typeof CallNode* */
//		CallNode* callNode = dynamic_cast<CallNode*>(node);
//		Assert::IsNotNull(callNode);
//
//		/*Ensures that callNode is valid*/
//		callNode->validate();
//
//		Assert::IsTrue(callNode->getLineNumber() == 1);
//		Assert::IsTrue(callNode->getProcedureName() == "FooProc");
//
//		for (auto token : tokensList) {
//			delete token;
//		}
//
//		tokensList.clear();
//		delete node;
	}

	TEST_METHOD(Parser_parseExpression) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "FooProc", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));

		/*Check if didn't receive a nullptr*/
		Node* node = Parser::parseExpression(tokensList.begin());

		for (auto token : tokensList) {
			delete token;
		}

		tokensList.clear();
		delete node;
	}

	
};