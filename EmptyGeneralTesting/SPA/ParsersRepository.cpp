#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
	expressionParser = nullptr;
	assignParser = nullptr;
	callParser = nullptr;
	whileParser = nullptr;
	ifparser = nullptr;
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
	delete assignParser;
	delete callParser;
	delete whileParser;
	delete ifparser;
}
