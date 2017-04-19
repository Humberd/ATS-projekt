#include "ParsingEntity.h"
#include "ParserException.h"

ParsingEntity::ParsingEntity(vector<LexerToken*>::iterator& iterator,
                             vector<LexerToken*>::iterator& iteratorEnd): iterator(iterator), iteratorEnd(iteratorEnd) {
}

ParsingEntity::~ParsingEntity() {
}

void ParsingEntity::nextElement() const {
	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw ParserException(getClassName() + " - Unexpected end of file");
	}
}

string ParsingEntity::getClassName() const {
	return string(typeid(*this).name());
}
