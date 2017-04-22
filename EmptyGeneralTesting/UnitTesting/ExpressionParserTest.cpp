#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ExpressionParser.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/Operators.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/PlusNode.h"
#include "../SPA/ConstantNode.h"
#include "../SPA/VariableNode.h"
#include "../SPA/TimesNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ExpressionParserTest) {
	TEST_METHOD(ExpressionParser_parse_Valid_testCase1) {
		vector<LexerToken*> tokensList;
		/*x + y * 5 + 4; */
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

		/*A tree should look like this
		 *1.					+
		 *2.			+				4
		 *3.		x		*
		 *4.			  y   5
		 */

		/*Line 1*/
		Assert::IsNotNull(dynamic_cast<PlusNode*>(node));
		Assert::IsTrue(node->getChildren().size() == 2);

		/*Line 2*/
		PlusNode* c1left = dynamic_cast<PlusNode*>(node->getChild(0));
		ConstantNode* c1right = dynamic_cast<ConstantNode*>(node->getChild(1));
		Assert::IsNotNull(c1left);
		Assert::IsTrue(c1left->getChildren().size() == 2);
		Assert::IsNotNull(c1right);
		Assert::IsTrue(c1right->getValue() == 4);

		/*Line 3*/
		VariableNode* c2left = dynamic_cast<VariableNode*>(c1left->getChild(0));
		TimesNode* c2right = dynamic_cast<TimesNode*>(c1left->getChild(1));
		Assert::IsNotNull(c2left);
		Assert::IsTrue(c2left->getName() == "x");
		Assert::IsNotNull(c2right);
		Assert::IsTrue(c2right->getChildren().size() == 2);

		/*Line 4*/
		VariableNode* c3left = dynamic_cast<VariableNode*>(c2right->getChild(0));
		ConstantNode* c3right = dynamic_cast<ConstantNode*>(c2right->getChild(1));
		Assert::IsNotNull(c3left);
		Assert::IsTrue(c3left->getName() == "y");
		Assert::IsNotNull(c3right);
		Assert::IsTrue(c3right->getValue() == 5);


		for (auto token : tokensList) {
			delete token;
		}
	}
};
