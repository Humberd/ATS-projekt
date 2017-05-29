#include "QParsersRepository.h"

QParsersRepository::QParsersRepository() {
	selectParser = nullptr;
	variableParser = nullptr;
	methodParser = nullptr;
	methodManyParser = nullptr;
	withParser = nullptr;
	withManyParser = nullptr;
}

QParsersRepository::~QParsersRepository() {
	delete selectParser;
	delete variableParser;
	delete methodParser;
	delete methodManyParser;
	delete withParser;
	delete withManyParser;
}
