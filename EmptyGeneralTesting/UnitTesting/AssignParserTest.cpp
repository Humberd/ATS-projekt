#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/LexerToken.h"
#include <vector>
#include "../SPA/TokenKeys.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/ExpressionParser.h"
#include "ExpressionParserMock.h"
#include "../SPA/AssignParser.h"
#include "../SPA/AssignNode.h"
#include "../SPA/VariableNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(AssignParserTest) {
	TEST_METHOD(AssignParser_parse_Valid_testCase1) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::EQUALS_SIGN, 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;
		parsersRepository->expressionParser = new ExpressionParserMock(parsersRepository, iterator, iteratorEnd);

		AssignParser* assParser = new AssignParser(parsersRepository, iterator, iteratorEnd);

		auto node = assParser->parse();
		node->validate();

		/*
		 * A tree should look like this:
		 * 1.			assignNode
		 * 2.		x				<exprNode>
		 */

		/*1st line*/
		Assert::IsNotNull(dynamic_cast<AssignNode*>(node));
		Assert::IsTrue(node->getChildren().size() == 2);

		/*2nd line*/
		VariableNode* c1left = dynamic_cast<VariableNode*>(node->getChild(0));
		ExpressionNode* c1right = dynamic_cast<ExpressionNode*>(node->getChild(1));
		Assert::IsNotNull(c1left);
		Assert::IsTrue(c1left->getName() == "x");
		Assert::IsNotNull(c1right);

		for (auto token : tokensList) {
			delete token;
		}
		delete node , assParser , parsersRepository;
	}

};
