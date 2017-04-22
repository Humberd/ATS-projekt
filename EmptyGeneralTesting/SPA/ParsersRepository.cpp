#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
	expressionParser = nullptr;
	assignParser = nullptr;
	callParser = nullptr;
	whileParser = nullptr;
	ifParser = nullptr;
	statementListParser = nullptr;
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
	delete assignParser;
	delete callParser;
	delete whileParser;
	delete ifParser;
	delete statementListParser;
}
