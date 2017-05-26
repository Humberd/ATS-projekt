#include "DParsersRepository.h"
#include "DParsingEntity.h"

DParsersRepository::DParsersRepository() {
	declarationParser = nullptr;
}

DParsersRepository::~DParsersRepository() {
	delete declarationParser;
}
