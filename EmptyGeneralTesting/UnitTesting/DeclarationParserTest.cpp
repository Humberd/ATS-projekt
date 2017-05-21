#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/DParsersRepository.h"
#include "../SPA/DeclarationParser.h"
#include "../SPA/QParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(DeclarationParserTest) {
	TEST_METHOD(DeclarationParser_parse_Valid_testCase1) {
		vector<QLexerToken*> tokensList;

		tokensList.push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::ASSIGN));
		tokensList.push_back(new QLexerToken(QTokenKeys::NAME, "a"));
		tokensList.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		DParsersRepository* parsersRepository = new DParsersRepository;

		DeclarationParser* declarationParser = new DeclarationParser(parsersRepository, iterator, iteratorEnd);

		auto declaredVariable = declarationParser->parse();

		Assert::IsNotNull(declaredVariable);
		Assert::IsTrue(declaredVariable->getType() == DeclarationKeywords::ASSIGN);
		Assert::IsTrue(declaredVariable->getName() == "a");

		for (auto token : tokensList) {
			delete token;
		}
		delete parsersRepository , declarationParser , declaredVariable;
	}

	TEST_METHOD(DeclarationParser_parse_Invalid) {
		vector<vector<QLexerToken*>*> invalidCasesList;

		vector<QLexerToken*>* list = new vector<QLexerToken*>();
		//empty case
		invalidCasesList.push_back(list);

		/*Must end with semicolon*/
		list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::CALL));
		list->push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		invalidCasesList.push_back(list);

		/*Must have a name, not the integer as a name*/
		list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::CALL));
		list->push_back(new QLexerToken(QTokenKeys::INTEGER, "1234"));
		list->push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));
		invalidCasesList.push_back(list);

		/*Must have a proper type at the beginning*/
		list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, "foo hello type"));
		list->push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		list->push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));
		invalidCasesList.push_back(list);

		/*Must have a declared name*/
		list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::ASSIGN));
		list->push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));
		invalidCasesList.push_back(list);

		for (auto caseList : invalidCasesList) {
			auto iterator = caseList->begin();
			auto iteratorEnd = caseList->end();

			DParsersRepository* parsersRepository = new DParsersRepository;

			DeclarationParser* declarationParser = new DeclarationParser(parsersRepository, iterator, iteratorEnd);

			auto pointer = [declarationParser] {
				declarationParser->parse();
			};

			Assert::ExpectException<QParserException>(pointer);

			delete declarationParser, parsersRepository;
		}

		for (auto caseList : invalidCasesList) {
			for (auto token : *caseList) {
				delete token;
			}
			delete caseList;
		}

		invalidCasesList.clear();
	}
};
