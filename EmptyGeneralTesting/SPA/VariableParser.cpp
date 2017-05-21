#include "VariableParser.h"
#include "QParserException.h"

VariableParser::VariableParser(QParsersRepository* parsersRepo,
                               vector<QLexerToken*>::iterator& lexerToken,
                               vector<QLexerToken*>::iterator& iteratorEnd) : QParsingEntity(parsersRepo, lexerToken, iteratorEnd) {
}

VariableParser::~VariableParser() {
}

QueryVariable* VariableParser::parse() {
	QueryVariable* queryVariable = new QueryVariable;

	throwOnEOF();

	if ((*iterator)->isName()) {
		queryVariable->setName((*iterator)->getValue());
	} else {
		throw QParserException(getClassName() + " - expected a variable name, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	/*variable has only a name, for example: myName*/
	if (iterator == iteratorEnd ||
		!(*iterator)->isDot()) {
		return queryVariable;
	}

	/*variable must have a proprtyName as well, for example: myName.procName*/
	if ((*iterator)->isDot()) {
		// do nothing
	} else {
		throw QParserException(getClassName() + " - expected a dot (.), but instead got: " + (*iterator)->toString());
	}
	nextElement();
	throwOnEOF();

	if ((*iterator)->isName()) {
		queryVariable->setPropertyName((*iterator)->getValue());
	} else {
		throw QParserException(getClassName() + " - expected a property name, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	/*Check if a variable has a redundant hash at the end*/
	if (iterator != iteratorEnd &&
		(*iterator)->isHash()) {
		// do nothing, just skip the hash in the iterator
		nextElement();
	}

	return queryVariable;
}
