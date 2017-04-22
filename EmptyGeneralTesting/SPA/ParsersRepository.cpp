#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
	expressionParser = nullptr;
	assignParser = nullptr;
	callParser = nullptr;
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
	delete assignParser;
	delete callParser;
}
