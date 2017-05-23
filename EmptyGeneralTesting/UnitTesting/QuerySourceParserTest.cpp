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
#include "../SPA/QuerySourceParser.h"
#include "../SPA/QueryKeywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QuerySourceParserTest) {
	TEST_METHOD(QuerySourceParser_parse_Valid1_emptySelect) {
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
};
