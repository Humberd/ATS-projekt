#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QParsersRepository.h"
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/QuerySpecialCharacters.h"
#include "../SPA/SelectParser.h"
#include "../SPA/MethodParser.h"
#include "../SPA/QParserException.h"
#include "../SPA/QueryMethods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(MethodParserTest) {
	TEST_METHOD(MethodParser_parseString_Valid) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "bar"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto result = methodParser->parseString();

		Assert::IsTrue(result == "bar");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo , methodParser;
	}

	TEST_METHOD(MethodParser_parseString_Invalid) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, 1));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto pointer = [methodParser]() {
					methodParser->parseString();
				};

		Assert::ExpectException<QParserException>(pointer);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo , methodParser;
	}

	TEST_METHOD(MethodParser_parseParameter_Valid_integer) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "8"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto parameter = methodParser->parseParameter();

		Assert::IsNotNull(parameter);
		Assert::IsTrue(parameter->getType() == ParameterType::INTEGER);
		Assert::IsTrue(parameter->getIntegerValue() == 8);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo , methodParser , parameter;
	}

	TEST_METHOD(MethodParser_parseParameter_Valid_variable) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "foobar"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto parameter = methodParser->parseParameter();

		Assert::IsNotNull(parameter);
		Assert::IsTrue(parameter->getType() == ParameterType::VARIABLE);
		Assert::IsTrue(parameter->getVariableName() == "foobar");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodParser, parameter;
	}

	TEST_METHOD(MethodParser_parseParameter_Valid_string) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "barBarFoo"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto parameter = methodParser->parseParameter();

		Assert::IsNotNull(parameter);
		Assert::IsTrue(parameter->getType() == ParameterType::STRING);
		Assert::IsTrue(parameter->getStringValue() == "barBarFoo");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodParser, parameter;
	}

	TEST_METHOD(MethodParser_parseParameter_Valid_any) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::LOWDASH));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto parameter = methodParser->parseParameter();

		Assert::IsNotNull(parameter);
		Assert::IsTrue(parameter->getType() == ParameterType::ANY);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodParser, parameter;
	}

	TEST_METHOD(MethodParser_parse_Valid) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, QueryMethods::PARENT));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::OPENBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "11"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::CLOSEBRACE));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;

		MethodParser* methodParser = new MethodParser(repo, iterator, iteratorEnd);

		auto methodRequest = methodParser->parse();

		Assert::IsNotNull(methodRequest);
		Assert::IsTrue(methodRequest->getMethodName() == QueryMethods::PARENT);
		Assert::IsTrue(methodRequest->getGoDeep() == false);

		Assert::IsNotNull(methodRequest->getLeftParam());
		Assert::IsNotNull(methodRequest->getRightParam());

		Assert::IsTrue(methodRequest->getLeftParam()->getType() == ParameterType::VARIABLE);
		Assert::IsTrue(methodRequest->getLeftParam()->getVariableName() == "s");

		Assert::IsTrue(methodRequest->getRightParam()->getType() == ParameterType::INTEGER);
		Assert::IsTrue(methodRequest->getRightParam()->getIntegerValue() == 11);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodParser, methodRequest;
	}
};
