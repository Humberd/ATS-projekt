#include "ExpressionParser.h"
#include "ExpressionNode.h"
//#include <CppUnitTestLogger.h>
#include "ParserException.h"
#include "VariableNode.h"
#include "ConstantNode.h"
#include "PlusNode.h"
#include "MinusNode.h"
#include "TimesNode.h"
#include <map>
#include <algorithm>

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

/*
 * The main concept is the following:
 * From the given expression input: 'x + y * 5 + 4'
 * 1st step:
 * I spllit it into 2 arrays: 
 *  - expressionNodes: [x, y, 5, 4]
 *  - operatorNodes:   [+, *, +]
 *  
 * 2nd step:
 * Add weights to the operatorNodes:
 *	[+, *, +] => [1, 10000, 1] => [2, 10000, 1]
 *	In the last iteration every wight must be different,
 *	so I add additional weights to the nodes being to the left.
 *	The more a node is to the left, the more points it gets.
 *	
 * 3rd step:
 * I find the operatorNode with the highest weight and
 * add the children to it from the corresponding expressionNodes.
 *	[x, y, 5, 4]
 *		| /
 *	[+, *, +]
 *	
 *	'*' has the most weight, so I set its children to 'y' and the following one: '5'
 *	
 * 4th step:
 * I remove the operator and its children from both arrays.
 * And I put the operator in the place of one of its children
 * [x, *, 4]
 * [+, +]
 *  
 *  I REPEAT 3RD STEP TILL THERE IS NO OPERATORS LEFT.
 *  The last remaining expressionNode is the expression root
 */
Node* ExpressionParser::parse() {
	vector<ExpressionNode*> expressionNodes;
	vector<OperatorNode*> operatorNodes;

	//	throwEOF();
	throwOnEOF();

	int numberOfTimes = 0;
	int numberOfPlusMinus = 0;

	/*0 = requires name/integer
	 * 1 = requires operator
	 */
	int ct = 0;
	while (true) {
		throwOnEOF();
		if ((*iterator)->isName() && ct == 0) {
			expressionNodes.push_back(new VariableNode((*iterator)->getSourceLineNumber(), (*iterator)->getValue()));
			ct = 1;
		} else if ((*iterator)->isInteger() && ct == 0) {
			expressionNodes.push_back(new ConstantNode((*iterator)->getSourceLineNumber(), stoi((*iterator)->getValue())));
			ct = 1;
		} else if ((*iterator)->isOperator() && ct == 1) {
			/*For every operator I set a default WEIGHT
			 * The higher - the more important the operator is
			 */
			if ((*iterator)->isPlus()) {
				operatorNodes.push_back(new OperatorNode(PLUS_MINUS_WEIGHT, new PlusNode((*iterator)->getSourceLineNumber())));
				++numberOfPlusMinus;
			} else if ((*iterator)->isMinus()) {
				operatorNodes.push_back(new OperatorNode(PLUS_MINUS_WEIGHT, new MinusNode((*iterator)->getSourceLineNumber())));
				++numberOfPlusMinus;
			} else if ((*iterator)->isTimes()) {
				operatorNodes.push_back(new OperatorNode(TIMES_WEIGHT, new TimesNode((*iterator)->getSourceLineNumber())));
				++numberOfTimes;
			} else {
				throw ParserException(getClassName() + " - expected plus, minus or times operator, but instead got: " + (*iterator)->toString());
			}

			ct = 0;
		} else if ((*iterator)->isSemicolon() && ct == 1) {
			nextElement();
			break;
		} else if ((*iterator)->isParenthesisOpen() || (*iterator)->isParenthesisClose()) {
			nextElement();
			continue;
		} else {
			if (ct == 0) {
				throw ParserException(getClassName() + " - expected name or integer, but instead got: " + (*iterator)->toString());
			} else {
				throw ParserException(getClassName() + " - expected operator, but instead got: " + (*iterator)->toString());
			}
		}

		nextElement();
	}

	/*I've counted how many are there plus, minus and times nodes (variables: numberOfTimes, numberOfPlusMinus).
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

	/*I find the operator with the highest weight till there is none left.
	 * Next to that operator I add 2 children from expressionNodes,
	 * one with the same index in the array and the next following.
	 * Next I remore 1 of the children from the array and the operator
	 * Next I put the operator to the expressionNodes instead of one of that 2 children.
	 */
	while (operatorNodes.size() > 0) {
		auto hwNode = findWithHighestWeight(operatorNodes);

		hwNode->operatorNode->addChild(expressionNodes.at(hwNode->index));
		hwNode->operatorNode->addChild(expressionNodes.at(hwNode->index + 1));

		operatorNodes.erase(operatorNodes.begin() + hwNode->index);
		expressionNodes.erase(expressionNodes.begin() + hwNode->index + 1);

		expressionNodes.at(hwNode->index) = hwNode->operatorNode;
	}

	/*The last remaining in the expressionNodes is the current root node*/
	if (expressionNodes.size() != 1) {
		throw ParserException("ExpressionNodes vector's size is not 1!");
	}

	return expressionNodes.at(0);
}

/*Find the OperatorNode with the highest weight and add to it its index in the list*/
OperatorNode* ExpressionParser::findWithHighestWeight(vector<OperatorNode*>& vector) {
	auto highest = max_element(vector.begin(), vector.end(),
	                           [](OperatorNode* node1, OperatorNode* node2) {
		                           return node1->weight < node2->weight;
	                           });
	OperatorNode* highestPointer = *highest;

	highestPointer->index = distance(vector.begin(), highest);

	return highestPointer;
}
