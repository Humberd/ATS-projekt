#include "ExpressionParser.h"
#include "ExpressionNode.h"
#include "rx.hpp"
#include "rx-subscriber.hpp"
#include <CppUnitTestLogger.h>
#include "ParserException.h"
#include "VariableNode.h"
#include "ConstantNode.h"
#include "PlusNode.h"
#include "MinusNode.h"
#include "TimesNode.h"

namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::sources;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

using namespace Rx;

ExpressionParser::ExpressionParser(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

Node* ExpressionParser::parse() {
	vector<ExpressionNode*> expressionNodes;
	Node* leftExpr;

	if ((*iterator)->isName()) {
		leftExpr = new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
	} else {
		throw ParserException(getClassName() + " - expected a name, but instead got: " + (*iterator)->toString());
	}
	nextElement();

	if ((*iterator)->isEquals()) {
		//empty
	} else {
		throw ParserException(getClassName() + " - expected an equals sign, but instead got: " + (*iterator)->toString());
	}
	nextElement();


	/*/*0 = requires name/integer
	 * 1 = requires operator
	 #1#
	int ct = 0;

	while (!(*iterator)->isSemicolon()) {
		if ((*iterator)->isName() && ct == 0) {
			expressionNodes.push_back(new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue()));
			ct = 1;
		} else if ((*iterator)->isInteger() && ct == 0) {
			expressionNodes.push_back(new ConstantNode((*iterator)->getFileLineNumber(), stoi((*iterator)->getValue())));
			ct = 1;
		} else if ((*iterator)->isOperator() && ct == 1) {
			if ((*iterator)->isPlus()) {
				expressionNodes.push_back(new PlusNode((*iterator)->getFileLineNumber()));
			} else if ((*iterator)->isMinus()) {
				expressionNodes.push_back(new MinusNode((*iterator)->getFileLineNumber()));
			} else if ((*iterator)->isTimes()) {
				expressionNodes.push_back(new TimesNode((*iterator)->getFileLineNumber()));
			} else {
				throw ParserException(getClassName() + " - expected plus, minus or times operator, but instead got: " + (*iterator)->toString());
			}

			ct = 0;
		} else {
			if (ct == 0) {
				throw ParserException(getClassName() + " - expected name or integer, but instead got: " + (*iterator)->toString());
			} else {
				throw ParserException(getClassName() + " - expected operator, but instead got: " + (*iterator)->toString());
			}
		}

		nextElement();
	}*/

	return nullptr;
}
