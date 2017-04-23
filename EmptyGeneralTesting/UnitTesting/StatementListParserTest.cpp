#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/StatementListParser.h"
#include "../SPA/SpecialCharacters.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/ParsersRepository.h"
#include "../SPA/ExpressionParser.h"
#include "../SPA/ParserException.h"
#include "IfParserMock.h"
#include "CallParserMock.h"
#include "AssignParserMock.h"
#include "ExpressionParserMock.h"
#include "StatementListParserMock.h"
#include "WhileParserMock.h"
#include "TokenKeyMocks.h"
#include "../SPA/StatementListNode.h"
#include "AssignNodeMock.h"
#include "CallNodeMock.h"
#include "IfNodeMock.h"
#include "WhileNodeMock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(StatementListParserTest) {
	TEST_METHOD(StatementListParser_parse_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::OPEN_BRACE, 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::ASSIGN_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::CALL_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::IF_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::WHILE_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::CLOSE_BRACE, 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		ParsersRepository* parsersRepository = new ParsersRepository;
		parsersRepository->assignParser = new AssignParserMock(parsersRepository, iterator, iteratorEnd);
		parsersRepository->callParser = new CallParserMock(parsersRepository, iterator, iteratorEnd);
		parsersRepository->ifParser = new IfParserMock(parsersRepository, iterator, iteratorEnd);
		parsersRepository->expressionParser = new ExpressionParserMock(parsersRepository, iterator, iteratorEnd);
		parsersRepository->statementListParser = new StatementListParserMock(parsersRepository, iterator, iteratorEnd);
		parsersRepository->whileParser = new WhileParserMock(parsersRepository, iterator, iteratorEnd);

		auto statementListParser = new StatementListParser(parsersRepository, iterator, iteratorEnd);

		Node* node = statementListParser->parse();
		node->validate();
		/*A tree should look like this
		 *1.							stmtLstNode
		 *2.	<assignNode>	<callNode>		<ifNode>		<whileNode>
		 */

		StatementListNode* stmLstNode = dynamic_cast<StatementListNode*>(node);
		Assert::IsNotNull(stmLstNode);
		Assert::IsTrue(stmLstNode->getChildren().size() == 4);

		AssignNodeMock* assignNode = dynamic_cast<AssignNodeMock*>(stmLstNode->getChild(0));
		Assert::IsNotNull(assignNode);

		CallNodeMock* callNode = dynamic_cast<CallNodeMock*>(stmLstNode->getChild(1));
		Assert::IsNotNull(callNode);

		IfNodeMock* ifNode = dynamic_cast<IfNodeMock*>(stmLstNode->getChild(2));
		Assert::IsNotNull(ifNode);

		WhileNodeMock* whileNode = dynamic_cast<WhileNodeMock*>(stmLstNode->getChild(3));
		Assert::IsNotNull(whileNode);

	}

	TEST_METHOD(StatementListParser_parse_Invalid) {
		vector<vector<LexerToken*>*> invalidCasesList;

		vector<LexerToken*>* list = new vector<LexerToken*>();
		//empty case
		invalidCasesList.push_back(list);

		/*don't have at least 1 statement*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::OPEN_BRACE, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::CLOSE_BRACE, 1));
		invalidCasesList.push_back(list);

		/*semicolon is not attached to anything*/
		list = new vector<LexerToken*>();
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::OPEN_BRACE, 1));
		list->push_back(new LexerToken(TokenKeyMocks::ASSIGN_MOCK, "", 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::SEMICOLON, 1));
		list->push_back(new LexerToken(TokenKeys::SPECIAL_CHARACTER, SpecialCharacters::CLOSE_BRACE, 1));
		invalidCasesList.push_back(list);

		for (vector<LexerToken*>* caseList : invalidCasesList) {
			auto iterator = caseList->begin();
			auto iteratorEnd = caseList->end();

			ParsersRepository* parsersRepository = new ParsersRepository;
			parsersRepository->assignParser = new AssignParserMock(parsersRepository, iterator, iteratorEnd);
			parsersRepository->callParser = new CallParserMock(parsersRepository, iterator, iteratorEnd);
			parsersRepository->ifParser = new IfParserMock(parsersRepository, iterator, iteratorEnd);
			parsersRepository->expressionParser = new ExpressionParserMock(parsersRepository, iterator, iteratorEnd);
			parsersRepository->statementListParser = new StatementListParserMock(parsersRepository, iterator, iteratorEnd);
			parsersRepository->whileParser = new WhileParserMock(parsersRepository, iterator, iteratorEnd);

			auto statementListParser = new StatementListParser(parsersRepository, iterator, iteratorEnd);

			auto pointer = [statementListParser] {
						statementListParser->parse();
					};

			Assert::ExpectException<ParserException>(pointer);

			for (LexerToken* token: *caseList) {
				delete token;
			}

			caseList->clear();

			delete parsersRepository , caseList, statementListParser;
		}
		invalidCasesList.clear();
	}
};
