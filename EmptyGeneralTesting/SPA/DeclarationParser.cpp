#include "DeclarationParser.h"
#include "DParsersRepository.h"
#include "QParserException.h"

DeclarationParser::DeclarationParser(DParsersRepository* parsersRepo,
                                     vector<QLexerToken*>::iterator& iterator,
                                     vector<QLexerToken*>::iterator& iteratorEnd) : DParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

DeclarationParser::~DeclarationParser() {
}

DeclaredVariable* DeclarationParser::parse() {
	string variableType;
	string variableName;

	throwOnEOF();

	if ((*iterator)->isDeclarationKeyword()) {
		variableType = (*iterator)->getValue();
	} else {
		throw QParserException(getClassName() + " - expected a declaration type, but instead got: " + (*iterator)->toString());
	}

	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		variableName = (*iterator)->getValue();
	} else {
		throw QParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}

	nextElement();
	throwOnEOF();

	if ((*iterator)->isSemicolon()) {
		//do nothing
	} else {
		throw QParserException(getClassName() + " - expected a semicolon, but instead got: " + (*iterator)->toString());
	}

	nextElement();

	return new DeclaredVariable(variableType, variableName);
}
