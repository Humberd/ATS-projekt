#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "TokenKeyMocks.h"
#include "../SPA/LexerToken.h"
#include "../SPA/ParsersRepository.h"
#include "ProcedureParserMock.h"
#include "../SPA/ProgramParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ProgramParserTest) {
	TEST_METHOD(ProgramParser_parse_Valid) {
		vector<LexerToken*> tokensList;

		tokensList.push_back(new LexerToken(TokenKeyMocks::PROCEDURE_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::PROCEDURE_MOCK, "", 1));
		tokensList.push_back(new LexerToken(TokenKeyMocks::PROCEDURE_MOCK, "", 1));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();
		ParsersRepository* parsersRepository = new ParsersRepository;
		parsersRepository->procedureParser = new ProcedureParserMock(parsersRepository, iterator, iteratorEnd);

		ProgramParser* programParser = new ProgramParser(parsersRepository, iterator, iteratorEnd);
		auto node = programParser->parse();

		for (auto token : tokensList) {
			delete token;
		}
		delete node , programParser , parsersRepository;
	}
};
