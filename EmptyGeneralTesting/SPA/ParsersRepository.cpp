#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
	expressionParser == nullptr;
	
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
}
