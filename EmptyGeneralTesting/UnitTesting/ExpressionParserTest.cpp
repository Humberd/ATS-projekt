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
#include "../SPA/ParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ExpressionParserTest) {

	TEST_METHOD(ExpressionParser_parse_Valid_testCase1) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::INTEGER, "10", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;

		ExpressionParser* expParser = new ExpressionParser(parsersRepository, iterator, iteratorEnd);

		auto node = expParser->parse();

		Assert::IsTrue(iterator == iteratorEnd);

		ConstantNode* constantNode = dynamic_cast<ConstantNode*>(node);
		Assert::IsNotNull(constantNode);
		Assert::IsTrue(constantNode->getValue() == 10);
		Assert::IsTrue(constantNode->getChildren().size() == 0);

		for (auto token : tokensList) {
			delete token;
		}
		delete node, expParser, parsersRepository;
	}

	TEST_METHOD(ExpressionParser_parse_Valid_testCase2) {
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

		Assert::IsTrue(iterator == iteratorEnd);

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

		delete node, expParser, parsersRepository;
	}

	TEST_METHOD(ExpressinParser_parse_Invalid) {
		vector<vector<LexerToken*>*> invalidCasesList;

		vector<LexerToken*>* list= new vector<LexerToken*>();
		//empty case
		invalidCasesList.push_back(list);

		/*need to have an operator between x and y*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		list->push_back(new LexerToken(TokenKeys::NAME, "y", 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		invalidCasesList.push_back(list);

		/*need to have a value after minus_sign*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		list->push_back(new LexerToken(TokenKeys::OPERATOR, Operators::MINUS_SIGN, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		invalidCasesList.push_back(list);

		/*don't have an operator between name and integer*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::NAME, "x", 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		invalidCasesList.push_back(list);

		/*cannot begin with operator*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::OPERATOR, Operators::MINUS_SIGN, 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		invalidCasesList.push_back(list);

		/*no semicolon*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		list->push_back(new LexerToken(TokenKeys::OPERATOR, Operators::TIMES_SIGN, 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		invalidCasesList.push_back(list);

		/*start with invalid character*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::EQUALS_SIGN, 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		list->push_back(new LexerToken(TokenKeys::OPERATOR, Operators::TIMES_SIGN, 1));
		list->push_back(new LexerToken(TokenKeys::INTEGER, "5", 1));
		invalidCasesList.push_back(list);

		ParsersRepository* parsersRepository = new ParsersRepository;

		for (auto caseList: invalidCasesList) {
			auto iterator = caseList->begin();
			auto iteratorEnd = caseList->end();
			
			ExpressionParser* expParser = new ExpressionParser(parsersRepository, iterator, iteratorEnd);

			auto pointer = [expParser] {
				expParser->parse();
			};

			Assert::ExpectException<ParserException>(pointer);

			delete expParser;
		}
		
		for (auto caseList : invalidCasesList) {
			for (auto token: *caseList) {
				delete token;
			}
			delete caseList;
		}

		delete parsersRepository;

		invalidCasesList.clear();
	}
};
