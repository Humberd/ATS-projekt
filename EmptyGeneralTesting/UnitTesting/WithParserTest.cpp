#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QParsersRepository.h"
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/WithParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(WithParserTest) {
	TEST_METHOD(WithParser_parse_Valid_integer) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "stmt"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::HASH));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "5"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		WithParser* withParser = new WithParser(repo, iterator, iteratorEnd);

		auto result = withParser->parse();

		Assert::IsNotNull(result);
		Assert::IsTrue(result->getType() == WithType::INTEGER);

		Assert::IsNotNull(result->getLeftSideVariable());
		Assert::IsTrue(result->getLeftSideVariable()->getName() == "s");
		Assert::IsTrue(result->getLeftSideVariable()->getPropertyName() == "stmt");

		Assert::IsTrue(result->getRightSideInteger() == 5);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, withParser;
	}
	TEST_METHOD(WithParser_parse_Valid_string) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "v"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "varName"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "myProcName"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		WithParser* withParser = new WithParser(repo, iterator, iteratorEnd);

		auto result = withParser->parse();

		Assert::IsNotNull(result);
		Assert::IsTrue(result->getType() == WithType::STRING);

		Assert::IsNotNull(result->getLeftSideVariable());
		Assert::IsTrue(result->getLeftSideVariable()->getName() == "v");
		Assert::IsTrue(result->getLeftSideVariable()->getPropertyName() == "varName");

		Assert::IsTrue(result->getRightSideString() == "myProcName");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, withParser;
	}
	TEST_METHOD(WithParser_parse_Valid_variable) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "v"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "varName"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "x"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "varName"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		WithParser* withParser = new WithParser(repo, iterator, iteratorEnd);

		auto result = withParser->parse();

		Assert::IsNotNull(result);
		Assert::IsTrue(result->getType() == WithType::VARIABLE);

		Assert::IsNotNull(result->getLeftSideVariable());
		Assert::IsTrue(result->getLeftSideVariable()->getName() == "v");
		Assert::IsTrue(result->getLeftSideVariable()->getPropertyName() == "varName");

		Assert::IsNotNull(result->getRightSideVariable());
		Assert::IsTrue(result->getRightSideVariable()->getName() == "x");
		Assert::IsTrue(result->getRightSideVariable()->getPropertyName() == "varName");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, withParser;
	}
};