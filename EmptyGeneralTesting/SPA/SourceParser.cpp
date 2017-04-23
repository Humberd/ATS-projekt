#include "SourceParser.h"
#include "ProgramNode.h"
#include "ExpressionParser.h"
#include "AssignParser.h"
#include "CallParser.h"
#include "WhileParser.h"
#include "StatementListParser.h"
#include "IfParser.h"
#include "ProgramParser.h"


SourceParser::SourceParser(vector<LexerToken*>& tokensList) : tokensList(tokensList) {
	auto iterator = tokensList.begin();
	auto iteratorEnd = tokensList.end();

	parsersRepo = new ParsersRepository;
	parsersRepo->expressionParser = new ExpressionParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->assignParser = new AssignParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->callParser = new CallParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->whileParser = new WhileParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->ifParser = new IfParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->statementListParser = new StatementListParser(parsersRepo, iterator, iteratorEnd);
	parsersRepo->programParser = new ProgramParser(parsersRepo, iterator, iteratorEnd);

}

SourceParser::~SourceParser() {
	delete parsersRepo;
}

Node* SourceParser::parse() {
	return parsersRepo->programParser->parse();
}

