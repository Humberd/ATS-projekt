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
#include "../SPA/QueryKeywords.h"
#include "../SPA/MethodManyParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(MethodManyParserTest) {
	TEST_METHOD(MethodManyParser_parse_Valid_1Method) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SUCH));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::THAT));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, QueryMethods::PARENT));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::OPENBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "11"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::CLOSEBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::WITH));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		MethodManyParser* methodManyParser = new MethodManyParser(repo, iterator, iteratorEnd);

		auto result = methodManyParser->parse();

		Assert::IsTrue(result.size() == 1);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodManyParser;
	}

	TEST_METHOD(MethodManyParser_parse_Valid_2Methods) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SUCH));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::THAT));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, QueryMethods::PARENT));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::OPENBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "11"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::CLOSEBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::AND));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, QueryMethods::CALLS));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::OPENBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "p"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "myProc"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::CLOSEBRACE));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		MethodManyParser* methodManyParser = new MethodManyParser(repo, iterator, iteratorEnd);

		auto result = methodManyParser->parse();

		Assert::IsTrue(result.size() == 2);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, methodManyParser;
	}
};