#include "ParsersRepository.h"

ParsersRepository::ParsersRepository() {
}

ParsersRepository::~ParsersRepository() {
	delete expressionParser;
}
