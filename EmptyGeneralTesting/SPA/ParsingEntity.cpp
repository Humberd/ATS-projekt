#include "ParsingEntity.h"
#include "ParserException.h"

ParsingEntity::ParsingEntity() {
}

ParsingEntity::~ParsingEntity() {
}

void ParsingEntity::nextElement(vector<LexerToken*>::iterator& iterator) const{
	try {
		++iterator;
	} catch (exception& e) {
		throw ParserException(string(typeid(this).name()) + " - Unexpected end of file");
	}
}


string ParsingEntity::getClassName() {
	return string(typeid(this).name());
}
