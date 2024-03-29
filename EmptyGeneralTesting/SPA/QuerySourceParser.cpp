#include "QuerySourceParser.h"
#include "QParsersRepository.h";
#include "QParserException.h"

QuerySourceParser::QuerySourceParser(QParsersRepository* parsersRepo,
                                     vector<QLexerToken*>::iterator& lexerToken,
                                     vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

QuerySourceParser::~QuerySourceParser() {
}

QueryRequest* QuerySourceParser::parse() const {
	QueryRequest* queryRequest = new QueryRequest;

	throwOnEOF();

	queryRequest->setReturnRequest(parsersRepo->selectParser->parse());

	if (iterator == iteratorEnd) {
		return queryRequest;
	}

	if ((*iterator)->isSuch()) {
		queryRequest->setMethodRequests(parsersRepo->methodManyParser->parse());

		if (iterator != iteratorEnd && (*iterator)->isWith()) {
			queryRequest->setWithRequests(parsersRepo->withManyParser->parse());
		}
	} else if ((*iterator)->isWith()) {
		queryRequest->setWithRequests(parsersRepo->withManyParser->parse());

		if (iterator != iteratorEnd && (*iterator)->isSuch()) {
			queryRequest->setMethodRequests(parsersRepo->methodManyParser->parse());
		}
	}

	if (iterator != iteratorEnd) {
		throw QParserException(getClassName() + " - expected end query, but instead got: " + (*iterator)->toString());
	}

	return queryRequest;
}

QueryRequest* QuerySourceParser::cleanParse(vector<QLexerToken*>& tokens) {
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

	delete repo, querySourceParser;

	return result;
}
