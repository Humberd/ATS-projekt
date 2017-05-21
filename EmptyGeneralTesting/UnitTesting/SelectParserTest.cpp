#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QParsersRepository.h"
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/SelectParser.h"
#include "../SPA/QueryKeywords.h"
#include "../SPA/QParsersRepository.h";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SelectParserTest) {
	TEST_METHOD(SelectParser_parseTouple_Valid_testCase1) {
		vector<QLexerToken*> toupleTokens;

		/*<foo, bar>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONBRACEOPEN));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONDBRACECLOSE));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto touple = selectParser->parseTouple();

		Assert::IsTrue(touple.size() == 2);
		Assert::IsTrue(touple.at(0)->getName() == "foo");
		Assert::IsTrue(touple.at(1)->getName() == "bar");

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}
	TEST_METHOD(SelectParser_parseTouple_Valid_testCase2) {
		vector<QLexerToken*> toupleTokens;

		/*<foo>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONBRACEOPEN));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONDBRACECLOSE));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto touple = selectParser->parseTouple();

		Assert::IsTrue(touple.size() == 1);
		Assert::IsTrue(touple.at(0)->getName() == "foo");

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}

	TEST_METHOD(SelectParser_parse_Valid_testCase1) {
		vector<QLexerToken*> toupleTokens;

		/*<foo>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONBRACEOPEN));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONDBRACECLOSE));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto returnRequest = selectParser->parse();

		Assert::IsNotNull(returnRequest);
		Assert::IsTrue(returnRequest->getReturnType() == ReturnType::VARIABLES);
		Assert::IsTrue(returnRequest->getVariables().size() == 1);

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}

	TEST_METHOD(SelectParser_parse_Valid_testCase2) {
		vector<QLexerToken*> toupleTokens;

		/*<foo>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "procName"));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto returnRequest = selectParser->parse();

		Assert::IsNotNull(returnRequest);
		Assert::IsTrue(returnRequest->getReturnType() == ReturnType::VARIABLES);
		Assert::IsTrue(returnRequest->getVariables().size() == 1);
		Assert::IsTrue(returnRequest->getVariables().at(0)->getName() == "foo");
		Assert::IsTrue(returnRequest->getVariables().at(0)->getPropertyName() == "procName");

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}

	TEST_METHOD(SelectParser_parse_Valid_testCase3) {
		vector<QLexerToken*> toupleTokens;

		/*<foo>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::BOOLEAN));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto returnRequest = selectParser->parse();

		Assert::IsNotNull(returnRequest);
		Assert::IsTrue(returnRequest->getReturnType() == ReturnType::BOOLEAN);
		Assert::IsTrue(returnRequest->getVariables().size() == 0);

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}

	TEST_METHOD(SelectParser_parse_Valid_testCase4) {
		vector<QLexerToken*> toupleTokens;

		/*<foo>*/
		toupleTokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONBRACEOPEN));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "foo"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::NAME, "stmt"));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::HASH));
		toupleTokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DIAMONDBRACECLOSE));

		auto iterator = toupleTokens.begin();
		auto iteratorEnd = toupleTokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);

		SelectParser* selectParser = new SelectParser(repo, iterator, iteratorEnd);

		auto returnRequest = selectParser->parse();

		Assert::IsNotNull(returnRequest);
		Assert::IsTrue(returnRequest->getReturnType() == ReturnType::VARIABLES);
		Assert::IsTrue(returnRequest->getVariables().size() == 2);
		Assert::IsTrue(returnRequest->getVariables().at(0)->getName() == "foo");
		Assert::IsTrue(returnRequest->getVariables().at(0)->getPropertyName() == "");
		Assert::IsTrue(returnRequest->getVariables().at(1)->getName() == "bar");
		Assert::IsTrue(returnRequest->getVariables().at(1)->getPropertyName() == "stmt");

		for (auto toupleToken : toupleTokens) {
			delete toupleToken;
		}
		toupleTokens.clear();

		delete repo, selectParser;
	}
};
