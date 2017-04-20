#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ExpressionParser.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/Operators.h"
#include "../SPA/ParsersRepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ExpressionParserTest) {
	TEST_METHOD(ExpressionParser_parse_Valid_testCase1) {
		vector<LexerToken*> tokensList;
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::EQUALS_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::PLUS_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "y", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::TIMES_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::PLUS_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::INTEGER, "4", 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;

		ExpressionParser* expParser = new ExpressionParser(parsersRepository, iterator, iteratorEnd);

		expParser->parse();

		for (auto token : tokensList) {
			delete token;
		}
	}
};
