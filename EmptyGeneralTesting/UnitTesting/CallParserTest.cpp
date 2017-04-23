#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/SpecialCharacters.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/LexerToken.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/CallParser.h"
#include "../SPA/Keywords.h"
#include "../SPA/CallNode.h"
#include "../SPA/ParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(CallParserTest) {
	TEST_METHOD(CallParser_parse_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "myProc", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;

		CallParser* callParser = new CallParser(parsersRepository, iterator, iteratorEnd);

		auto node = callParser->parse();
		node->validate();

		Assert::IsTrue(iterator == iteratorEnd);

		CallNode* callNode = dynamic_cast<CallNode*>(node);
		Assert::IsNotNull(callNode);
		Assert::IsTrue(callNode->getProcedureName() == "myProc");

		for (auto token : tokensList) {
			delete token;
		}
		delete node, callParser, parsersRepository;
	}

	TEST_METHOD(CallParser_parse_Invalid) {
		vector<vector<LexerToken*>*> invalidCasesList;

		vector<LexerToken*>* list = new vector<LexerToken*>();
		//empty case
		invalidCasesList.push_back(list);

		/*must end with semicolon*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
		list->push_back(new LexerToken(TokenKeys::NAME, "myProc", 1));
		invalidCasesList.push_back(list);

		/*must have a name as second*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::CALL, 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "1", 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		invalidCasesList.push_back(list);

		ParsersRepository* parsersRepository = new ParsersRepository;

		for (auto caseList : invalidCasesList) {
			auto iterator = caseList->begin();
			auto iteratorEnd = caseList->end();

			CallParser* callParser = new CallParser(parsersRepository, iterator, iteratorEnd);

			auto pointer = [callParser] {
				callParser->parse();
			};

			Assert::ExpectException<ParserException>(pointer);

			delete callParser;
		}

		for (auto caseList : invalidCasesList) {
			for (auto token : *caseList) {
				delete token;
			}
			delete caseList;
		}
		delete parsersRepository;

		invalidCasesList.clear();
	}
};