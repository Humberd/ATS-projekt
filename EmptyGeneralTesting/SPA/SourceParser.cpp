#include "SourceParser.h"
#include "ProgramNode.h"
#include "ExpressionParser.h"
#include "AssignParser.h"


SourceParser::SourceParser(vector<LexerToken*>& tokensList) : tokensList(tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	parsersRepo = new ParsersRepository;
	parsersRepo->expressionParser = new ExpressionParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->assignParser = new AssignParser(parsersRepo, iterator, iteratorEnd);

}

SourceParser::~SourceParser() {
	delete parsersRepo;
}

Node* SourceParser::parse() {

	return nullptr;
}

