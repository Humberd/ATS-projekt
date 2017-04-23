#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/StatementListParser.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/AssignParser.h"
#include "../SPA/CallParser.h"
#include "../SPA/IfParser.h"
#include "../SPA/ExpressionParser.h"
#include "../SPA/ParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(StatementListParserTest) {
	TEST_METHOD(StatementListParser_parse_Valid) {

	}

	TEST_METHOD(StatementListParser_parse_Invalid) {
		vector<vector<LexerToken*>*> invalidCasesList;

		vector<LexerToken*>* list = new vector<LexerToken*>();
		//empty case
		invalidCasesList.push_back(list);

		/*must have at least 1 statement*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::OPEN_BRACE, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::CLOSE_BRACE, 1));
		invalidCasesList.push_back(list);

		/*must have a valid statement*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::OPEN_BRACE, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::CLOSE_BRACE, 1));
		invalidCasesList.push_back(list);

		for (vector<LexerToken*>* caseList : invalidCasesList) {
			auto iterator = caseList->begin();
			auto iteratorEnd = caseList->end();

			ParsersRepository* parsersRepository = new ParsersRepository;
			parsersRepository->assignParser = new AssignParser(parsersRepository, iterator, iteratorEnd);
			parsersRepository->callParser = new CallParser(parsersRepository, iterator, iteratorEnd);
			parsersRepository->ifParser = new IfParser(parsersRepository, iterator, iteratorEnd);
			parsersRepository->expressionParser = new ExpressionParser(parsersRepository, iterator, iteratorEnd);
			parsersRepository->statementListParser = new StatementListParser(parsersRepository, iterator, iteratorEnd);
			parsersRepository->whileParser = new StatementListParser(parsersRepository, iterator, iteratorEnd);

			auto pointer = [parsersRepository] {
						parsersRepository->statementListParser->parse();
					};

			Assert::ExpectException<ParserException>(pointer);

			for (LexerToken* token: *caseList) {
				delete token;
			}

			caseList->clear();

			delete parsersRepository , caseList;
		}
		invalidCasesList.clear();
	}
};
