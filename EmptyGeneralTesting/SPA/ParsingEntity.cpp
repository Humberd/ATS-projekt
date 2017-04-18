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
		throw ParserException(getClassName() + " - Unexpected end of file");
	}
}


string ParsingEntity::getClassName() const{
	return string(typeid(*this).name());
}
