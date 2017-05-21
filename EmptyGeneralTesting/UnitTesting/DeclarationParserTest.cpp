#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/DParsersRepository.h"
#include "../SPA/DeclarationParser.h"

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
	}
};
