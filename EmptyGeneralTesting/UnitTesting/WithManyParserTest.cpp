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
#include "../SPA/WithManyParser.h"
#include "../SPA/QueryKeywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(WithManyParserTest) {
	TEST_METHOD(WithManyParser_parse_Valid_1With) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::WITH));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "stmt"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::HASH));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "5"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->withParser = new WithParser(repo, iterator, iteratorEnd);
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		WithManyParser* withManyParser = new WithManyParser(repo, iterator, iteratorEnd);

		auto result = withManyParser->parse();

		Assert::IsTrue(result.size() == 1);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, withManyParser;
	}
	TEST_METHOD(WithManyParser_parse_Valid_2With) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::WITH));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "stmt"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::HASH));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "5"));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::AND));
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
		repo->withParser = new WithParser(repo, iterator, iteratorEnd);
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);

		WithManyParser* withManyParser = new WithManyParser(repo, iterator, iteratorEnd);

		auto result = withManyParser->parse();

		Assert::IsTrue(result.size() == 2);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, withManyParser;
	}
};