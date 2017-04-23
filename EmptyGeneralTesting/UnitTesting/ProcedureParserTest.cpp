#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/SpecialCharacters.h"
#include "../SPA/TokenKeys.h"
#include "../SPA/LexerToken.h"
#include "TokenKeyMocks.h"
#include "../SPA/Keywords.h"
#include "../SPA/ParsersRepository.h"
#include "StatementListParserMock.h"
#include "../SPA/ProcedureParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ProcedureParserTest) {
	TEST_METHOD(ProcedureParser_parse_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeys::KEYWORD, Keywords::PROCEDURE, 1));
		tokensList.push_back(new LexerToken(TokenKeys::NAME, "FooProc", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::STATEMENT_LIST_MOCK, "", 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;
		parsersRepository->statementListParser = new StatementListParserMock(parsersRepository, iterator, iteratorEnd);

		ProcedureParser* procedureParser = new ProcedureParser(parsersRepository, iterator, iteratorEnd);

		auto node = procedureParser->parse();
		/*dont' validate a node, because StatementListNode requires children*/

		for (auto token : tokensList) {
			delete token;
		}
		delete node, procedureParser, parsersRepository;
	}
};