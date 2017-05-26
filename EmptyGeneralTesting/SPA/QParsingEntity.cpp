#include "QParsingEntity.h"
#include "QParsersRepository.h"
#include "QParserException.h"

QParsingEntity::QParsingEntity(QParsersRepository* parsersRepo,
                               vector<QLexerToken*>::iterator& iterator,
                               vector<QLexerToken*>::iterator& iteratorEnd) : parsersRepo(parsersRepo), iterator(iterator), iteratorEnd(iteratorEnd) {
}

QParsingEntity::~QParsingEntity() {
}

void QParsingEntity::nextElement() const {
	if (iterator != iteratorEnd) {
		++iterator;
	} else {
		throw QParserException(getClassName() + " - Unexpected end of file");
	}
}

void QParsingEntity::throwOnEOF() const {
	if (iterator == iteratorEnd) {
		throw QParserException(getClassName() + " - Unexpected end of file");
	}
}

string QParsingEntity::getClassName() const {
	return string(typeid(*this).name());
}
