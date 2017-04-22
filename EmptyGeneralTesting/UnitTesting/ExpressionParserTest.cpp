#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ExpressionParser.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/Operators.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/PlusNode.h"
#include "../SPA/ConstantNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ExpressionParserTest) {
	TEST_METHOD(ExpressionParser_parse_Valid_testCase1) {
		vector<LexerToken*> tokensList;
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::PLUS_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "y", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::TIMES_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		tokensList.push_back(new LexerToken(TokenKeys::OPERATOR, Operators::PLUS_SIGN, 1));
		tokensList.push_back(new LexerToken(TokenKeys::INTEGER, "4", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;

		ExpressionParser* expParser = new ExpressionParser(parsersRepository, iterator, iteratorEnd);

		auto node = expParser->parse();
		node->validate();
		node->prettyPrint();

		Assert::IsNotNull(dynamic_cast<PlusNode*>(node));
		Assert::IsTrue(node->getChildren().size() == 2);
		PlusNode* c1left = dynamic_cast<PlusNode*>(node->getChild(0));
		ConstantNode* c1right = dynamic_cast<ConstantNode*>(node->getChild(1));
		Assert::IsNotNull(c1right);
		Assert::IsTrue(c1right->getValue() == 4);


		for (auto token : tokensList) {
			delete token;
		}
	}
};
