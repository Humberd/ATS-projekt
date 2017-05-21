#include "QParsersRepository.h"

QParsersRepository::QParsersRepository() {
	variableParser = nullptr;
}

QParsersRepository::~QParsersRepository() {
	delete variableParser;
}
