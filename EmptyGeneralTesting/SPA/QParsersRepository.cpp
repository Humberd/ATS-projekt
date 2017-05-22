#include "QParsersRepository.h"

QParsersRepository::QParsersRepository() {
	variableParser = nullptr;
	methodParser = nullptr;
}

QParsersRepository::~QParsersRepository() {
	delete variableParser;
	delete methodParser;
}
