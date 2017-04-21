#include "ParsingEntity.h"
#include "ParserException.h"

ParsingEntity::ParsingEntity(ParsersRepository* parsersRepo,
                             vector<LexerToken*>::iterator& iterator,
                             vector<LexerToken*>::iterator& iteratorEnd): parsersRepo(parsersRepo), iterator(iterator), iteratorEnd(iteratorEnd) {
}

ParsingEntity::~ParsingEntity() {
}

void ParsingEntity::nextElement() const {
	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw ParserException(getClassName() + " - Unexpected end of file: " + (*(iterator - 1))->toString());
	}
}

string ParsingEntity::getClassName() const {
	return string(typeid(*this).name());
}
