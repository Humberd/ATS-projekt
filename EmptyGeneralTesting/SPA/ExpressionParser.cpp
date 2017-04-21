#include "ExpressionParser.h"
#include "ExpressionNode.h"
#include <CppUnitTestLogger.h>
#include "ParserException.h"
#include "VariableNode.h"
#include "ConstantNode.h"
#include "PlusNode.h"
#include "MinusNode.h"
#include "TimesNode.h"
#include <map>
#include <algorithm>
#include "AssignNode.h"

OperatorNode::OperatorNode(int weight, ExpressionNode* operatorNode) : weight(weight),
                                                                       operatorNode(operatorNode) {
}

ExpressionParser::ExpressionParser(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

const int ExpressionParser::TIMES_WEIGHT = 10000;
const int ExpressionParser::PLUS_MINUS_WEIGHT = 1;

Node* ExpressionParser::parse() {
	vector<ExpressionNode*> expressionNodes;
	vector<OperatorNode*> operatorNodes;
	Node* leftExpr;
	Node* assignNode;

	if (iterator == iteratorEnd) {
		throw ParserException(getClassName() + " - Unexpected end of file");
	}

	if ((*iterator)->isName()) {
		leftExpr = new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue());
		assignNode = new AssignNode((*iterator)->getFileLineNumber());
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


	int numberOfTimes = 0;
	int numberOfPlusMinus = 0;

	/*0 = requires name/integer
	 * 1 = requires operator
	 */
	int ct = 0;

	while (true) {
		if (iterator == iteratorEnd) {
			throw ParserException(getClassName() + " - Unexpected end of file");
		}
		if ((*iterator)->isName() && ct == 0) {
			expressionNodes.push_back(new VariableNode((*iterator)->getFileLineNumber(), (*iterator)->getValue()));
			ct = 1;
		} else if ((*iterator)->isInteger() && ct == 0) {
			expressionNodes.push_back(new ConstantNode((*iterator)->getFileLineNumber(), stoi((*iterator)->getValue())));
			ct = 1;
		} else if ((*iterator)->isOperator() && ct == 1) {
			if ((*iterator)->isPlus()) {
				operatorNodes.push_back(new OperatorNode(PLUS_MINUS_WEIGHT, new PlusNode((*iterator)->getFileLineNumber())));
				++numberOfPlusMinus;
			} else if ((*iterator)->isMinus()) {
				operatorNodes.push_back(new OperatorNode(PLUS_MINUS_WEIGHT, new MinusNode((*iterator)->getFileLineNumber())));
				++numberOfPlusMinus;
			} else if ((*iterator)->isTimes()) {
				operatorNodes.push_back(new OperatorNode(TIMES_WEIGHT, new TimesNode((*iterator)->getFileLineNumber())));
				++numberOfTimes;
			} else {
				throw ParserException(getClassName() + " - expected plus, minus or times operator, but instead got: " + (*iterator)->toString());
			}

			ct = 0;
		} else if ((*iterator)->isSemicolon() && ct == 1) {
			break;
		} else {
			if (ct == 0) {
				throw ParserException(getClassName() + " - expected name or integer, but instead got: " + (*iterator)->toString());
			} else {
				throw ParserException(getClassName() + " - expected operator, but instead got: " + (*iterator)->toString());
			}
		}

		nextElement();
	}

	/*I've counted how many are there plus, minus and times nodes.
	 * Now for every node from left to right I add --numberOfOccurrance to its weight.
	 * So that when I get the nodes: [+, *, +, -] before this operation they have weights [1, 10000, 1, 1].
	 * After the operation [3, 1000, 2, 1]
	 */
	for (auto operatorNode : operatorNodes) {
		if (operatorNode->weight == TIMES_WEIGHT) {
			operatorNode->weight = operatorNode->weight + --numberOfTimes;
		} else if (operatorNode->weight == PLUS_MINUS_WEIGHT) {
			operatorNode->weight = operatorNode->weight + --numberOfPlusMinus;
		}
	}

	while (operatorNodes.size() > 0) {
		auto hwNode = findWithHighestWeight(operatorNodes);

		hwNode->operatorNode->addChild(expressionNodes.at(hwNode->index));
		hwNode->operatorNode->addChild(expressionNodes.at(hwNode->index + 1));

		operatorNodes.erase(operatorNodes.begin() + hwNode->index);
		expressionNodes.erase(expressionNodes.begin() + hwNode->index + 1);
		
		expressionNodes.at(hwNode->index) = hwNode->operatorNode;
	}

	if (expressionNodes.size() != 1) {
		throw ParserException("ExpressionNodes vector's size is not 1!");
	}

	assignNode->addChild(leftExpr);
	assignNode->addChild(expressionNodes.at(0));

	return assignNode;
}

OperatorNode* ExpressionParser::findWithHighestWeight(vector<OperatorNode*>& vector) {
	auto highest = max_element(vector.begin(), vector.end(),
	                           [](OperatorNode* node1, OperatorNode* node2) {
		                           return node1->weight < node2->weight;
	                           });
	OperatorNode* highestPointer = *highest;

	highestPointer->index = distance(vector.begin(), highest);

	return highestPointer;
}
