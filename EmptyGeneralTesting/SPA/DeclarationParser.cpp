#include "DeclarationParser.h"
#include "DParsersRepository.h"
#include "QParserException.h"

DeclarationParser::DeclarationParser(DParsersRepository* parsersRepo,
                                     vector<QLexerToken*>::iterator& iterator,
                                     vector<QLexerToken*>::iterator& iteratorEnd) : DParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

DeclarationParser::~DeclarationParser() {
}

vector<DeclaredVariable*> DeclarationParser::parse() {
	vector<DeclaredVariable*> variables;

	string variableType;

	throwOnEOF();

	if ((*iterator)->isDeclarationKeyword()) {
		variableType = (*iterator)->getValue();
	} else {
		throw QParserException(getClassName() + " - expected a declaration type, but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	while (iterator != iteratorEnd &&
		(*iterator)->isName()) {
		
		if ((*iterator)->isName()) {
			auto variable = new DeclaredVariable;
			variable->setType(variableType);
			variable->setName((*iterator)->getValue());
			variables.push_back(variable);
		} else {
			throw QParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
		}
		nextElement();
		throwOnEOF();

		if ((*iterator)->isComma()) {
			nextElement();
			throwOnEOF();
			continue;
		} else {
			break;
		}
	}

	if (variables.size() == 0) {
		throw QParserException(getClassName() + " - expected at least one variable name after a type declaration");
	}

	if ((*iterator)->isSemicolon()) {
		//do nothing
	} else {
		throw QParserException(getClassName() + " - expected a semicolon, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	return variables;
}
