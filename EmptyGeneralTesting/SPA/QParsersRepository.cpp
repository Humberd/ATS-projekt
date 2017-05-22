#include "QParsersRepository.h"

QParsersRepository::QParsersRepository() {
	variableParser = nullptr;
	methodParser = nullptr;
	withParser = nullptr;
}

QParsersRepository::~QParsersRepository() {
	delete variableParser;
	delete methodParser;
	delete withParser;
}
