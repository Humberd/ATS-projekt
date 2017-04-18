#include "ParsingEntity.h"
#include "ParserException.h"

template <class T>
ParsingEntity<T>::ParsingEntity() {
}

template <class T>
ParsingEntity<T>::~ParsingEntity() {
}

template <class T>
void ParsingEntity<T>::nextElement(vector<LexerToken*>::iterator& iterator) const{
	try {
		++iterator;
	} catch (exception& e) {
		throw ParserException(string(typeid(this).name()) + " - Unexpected end of file");
	}
}
