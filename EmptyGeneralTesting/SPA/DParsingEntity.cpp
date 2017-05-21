#include "DParsingEntity.h"
#include "QParserException.h"
#include "DParsersRepository.h"

DParsingEntity::DParsingEntity(DParsersRepository* parsersRepo,
                               vector<QLexerToken*>::iterator& iterator,
                               vector<QLexerToken*>::iterator& iteratorEnd) : parsersRepo(parsersRepo), iterator(iterator), iteratorEnd(iteratorEnd) {
}

DParsingEntity::~DParsingEntity() {
}


void DParsingEntity::nextElement() const {
	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw QParserException(getClassName() + " - Unexpected end of file");
	}
}

void DParsingEntity::throwOnEOF() const {
	if (iterator == iteratorEnd) {
		throw QParserException(getClassName() + " - Unexpected end of file");
	}
}

string DParsingEntity::getClassName() const {
	return string(typeid(*this).name());
}
