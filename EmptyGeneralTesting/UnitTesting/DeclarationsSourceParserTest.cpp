#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/QLexerToken.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/DParsersRepository.h"
#include "../SPA/DeclarationParser.h"
#include "../SPA/DeclarationsSourceParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(DeclarationsSourceParserTest) {
	TEST_METHOD(DeclarationsSourceParser_parse_Valid) {
		vector<QLexerToken*> tokensList;

		tokensList.push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::ASSIGN));
		tokensList.push_back(new QLexerToken(QTokenKeys::NAME, "a"));
		tokensList.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));

		tokensList.push_back(new QLexerToken(QTokenKeys::DECLARATION_KEYWORD, DeclarationKeywords::CALL));
		tokensList.push_back(new QLexerToken(QTokenKeys::NAME, "b"));
		tokensList.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::SEMICOLON));

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		DParsersRepository* parsersRepository = new DParsersRepository;
		parsersRepository->declarationParser = new DeclarationParser(parsersRepository, iterator, iteratorEnd);

		DeclarationsSourceParser* sourceParser = new DeclarationsSourceParser(tokensList);

		auto variables = sourceParser->parse();

		Assert::IsTrue(variables.size() == 2);

		Assert::IsTrue(variables.at(0)->getType() == DeclarationKeywords::ASSIGN);
		Assert::IsTrue(variables.at(0)->getName() == "a");

		Assert::IsTrue(variables.at(1)->getType() == DeclarationKeywords::CALL);
		Assert::IsTrue(variables.at(1)->getName() == "b");

		for (auto token : tokensList) {
			delete token;
		}
		tokensList.clear();

		for (auto variable : variables) {
			delete variable;
		}
		variables.clear();

		delete parsersRepository, sourceParser;
	}
};
