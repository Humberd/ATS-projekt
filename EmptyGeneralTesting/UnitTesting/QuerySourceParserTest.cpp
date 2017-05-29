#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QParsersRepository.h"
#include "../SPA/QLexerToken.h"
#include "../SPA/QTokenKeys.h"
#include "../SPA/SelectParser.h"
#include "../SPA/MethodParser.h"
#include "../SPA/QuerySourceParser.h"
#include "../SPA/QueryKeywords.h"
#include "../SPA/QueryMethods.h"
#include "../SPA/QuerySpecialCharacters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QuerySourceParserTest) {
	TEST_METHOD(QuerySourceParser_parse_Valid1_1VariableSelect) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "v"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->selectParser = new SelectParser(repo, iterator, iteratorEnd);
		repo->methodManyParser = new MethodManyParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->withManyParser = new WithManyParser(repo, iterator, iteratorEnd);
		repo->withParser = new WithParser(repo, iterator, iteratorEnd);

		QuerySourceParser* querySourceParser = new QuerySourceParser(repo, iterator, iteratorEnd);

		auto result = querySourceParser->parse();

		Assert::IsNotNull(result);

		Assert::IsTrue(result->getMethodRequests().size() == 0);
		Assert::IsTrue(result->getWithRequests().size() == 0);

		Assert::IsNotNull(result->getReturnRequest());
		Assert::IsTrue(result->getReturnRequest()->getReturnType() == ReturnType::VARIABLES);
		Assert::IsTrue(result->getReturnRequest()->getVariables().size() == 1);
		Assert::IsTrue(result->getReturnRequest()->getVariables().at(0)->getName() == "v");
		Assert::IsTrue(result->getReturnRequest()->getVariables().at(0)->getPropertyName().empty());

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo , querySourceParser , result;
	}

	TEST_METHOD(QuerySourceParser_parse_Valid2_complexMethodWithWith) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "p"));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SUCH));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::THAT));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_METHOD, QueryMethods::USES));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::OPENBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "p"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::COMMA));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "e"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::CLOSEBRACE));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::WITH));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "p"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "procName"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "q"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::QUOTATIONMARK));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->selectParser = new SelectParser(repo, iterator, iteratorEnd);
		repo->methodManyParser = new MethodManyParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->withManyParser = new WithManyParser(repo, iterator, iteratorEnd);
		repo->withParser = new WithParser(repo, iterator, iteratorEnd);

		QuerySourceParser* querySourceParser = new QuerySourceParser(repo, iterator, iteratorEnd);

		auto result = querySourceParser->parse();

		Assert::IsNotNull(result);

		Assert::IsNotNull(result->getReturnRequest());
		Assert::IsTrue(result->getReturnRequest()->getReturnType() == ReturnType::VARIABLES);
		Assert::IsTrue(result->getReturnRequest()->getVariables().size() == 1);
		Assert::IsNotNull(result->getReturnRequest()->getVariables().at(0));
		Assert::IsTrue(result->getReturnRequest()->getVariables().at(0)->getName() == "p");
		Assert::IsTrue(result->getReturnRequest()->getVariables().at(0)->getPropertyName().empty());

		Assert::IsTrue(result->getMethodRequests().size() == 1);
		Assert::IsNotNull(result->getMethodRequests().at(0));
		Assert::IsTrue(result->getMethodRequests().at(0)->getMethodName() == QueryMethods::USES);
		Assert::IsTrue(result->getMethodRequests().at(0)->getGoDeep() == false);
		Assert::IsNotNull(result->getMethodRequests().at(0)->getLeftParam());
		Assert::IsTrue(result->getMethodRequests().at(0)->getLeftParam()->getType() == ParameterType::VARIABLE);
		Assert::IsTrue(result->getMethodRequests().at(0)->getLeftParam()->getVariableName() == "p");
		Assert::IsNotNull(result->getMethodRequests().at(0)->getRightParam());
		Assert::IsTrue(result->getMethodRequests().at(0)->getRightParam()->getType() == ParameterType::STRING);
		Assert::IsTrue(result->getMethodRequests().at(0)->getRightParam()->getStringValue() == "e");

		Assert::IsTrue(result->getWithRequests().size() == 1);
		Assert::IsNotNull(result->getWithRequests().at(0));
		Assert::IsNotNull(result->getWithRequests().at(0)->getLeftSideVariable());
		Assert::IsTrue(result->getWithRequests().at(0)->getLeftSideVariable()->getName() == "p");
		Assert::IsTrue(result->getWithRequests().at(0)->getLeftSideVariable()->getPropertyName() == "procName");
		Assert::IsTrue(result->getWithRequests().at(0)->getType() == WithType::STRING);
		Assert::IsTrue(result->getWithRequests().at(0)->getRightSideString() == "q");

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo , querySourceParser , result;
	}

	TEST_METHOD(QuerySourceParser_parse_Valid3_1VariableSelectAnd1With) {
		vector<QLexerToken*> tokens;

		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::SELECT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "v"));
		tokens.push_back(new QLexerToken(QTokenKeys::QUERY_KEYWORD, QueryKeywords::WITH));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "s"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::DOT));
		tokens.push_back(new QLexerToken(QTokenKeys::NAME, "stmt"));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::HASH));
		tokens.push_back(new QLexerToken(QTokenKeys::SPECIAL_CHARACTER, QuerySpecialCharacters::EQUALS));
		tokens.push_back(new QLexerToken(QTokenKeys::INTEGER, "90"));

		auto iterator = tokens.begin();
		auto iteratorEnd = tokens.end();

		QParsersRepository* repo = new QParsersRepository;
		repo->selectParser = new SelectParser(repo, iterator, iteratorEnd);
		repo->methodManyParser = new MethodManyParser(repo, iterator, iteratorEnd);
		repo->methodParser = new MethodParser(repo, iterator, iteratorEnd);
		repo->variableParser = new VariableParser(repo, iterator, iteratorEnd);
		repo->withManyParser = new WithManyParser(repo, iterator, iteratorEnd);
		repo->withParser = new WithParser(repo, iterator, iteratorEnd);

		QuerySourceParser* querySourceParser = new QuerySourceParser(repo, iterator, iteratorEnd);

		auto result = querySourceParser->parse();

		Assert::IsNotNull(result);

		for (auto token : tokens) {
			delete token;
		}
		tokens.clear();

		delete repo, querySourceParser, result;
	}
};
