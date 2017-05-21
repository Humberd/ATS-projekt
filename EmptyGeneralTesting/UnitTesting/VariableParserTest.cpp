#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/QParsersRepository.h"
#include "../SPA/VariableParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(VariableParserTest) {
	TEST_METHOD(VariableParser_parse_Valid) {
		vector<vector<QLexerToken*>*> testCases;

		vector<QLexerToken*>* list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		testCases.push_back(list);

		list = new vector<QLexerToken*>();
		list->push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		list->push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		list->push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		testCases.push_back(list);

		string expRes[2][2] = {
			{"foo", ""},
			{"foo", "bar"}
		};

		for (int i = 0; i < testCases.size(); i++) {
			auto testCase = testCases.at(i);

			QParsersRepository* qParsersRepository = new QParsersRepository;

			auto iterator = testCase->begin();
			auto iteratorEnd = testCase->end();

			VariableParser* variableParser = new VariableParser(qParsersRepository, iterator, iteratorEnd);

			auto queryVariable = variableParser->parse();

			Assert::IsNotNull(queryVariable);
			Assert::IsTrue(queryVariable->getName() == expRes[i][0]);
			Assert::IsTrue(queryVariable->getPropertyName() == expRes[i][1]);

			for (int j = 0; j < testCase->size(); j++) {
				delete testCase->at(j);
			}
			delete testCase;
			delete qParsersRepository , variableParser;
		}

		testCases.clear();
	}
};
