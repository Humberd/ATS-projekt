#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
	expressionParser = nullptr;
	assignParser = nullptr;
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
	delete assignParser;
}
