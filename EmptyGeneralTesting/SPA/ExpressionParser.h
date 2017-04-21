#pragma once
#include <vector>
#include "LexerToken.h"
#include "Node.h"
#include "ParsingEntity.h"
#include "ExpressionNode.h"

using namespace std;

class OperatorNode {
public:
	int weight;
	ExpressionNode* operatorNode;
	int index;

	OperatorNode(int weight, ExpressionNode* operatorNode);
};

class ExpressionParser: public ParsingEntity {
public:
	static const int TIMES_WEIGHT;
	static const int PLUS_MINUS_WEIGHT;

	explicit ExpressionParser(ParsersRepository* parsersRepo,
	                          vector<LexerToken*>::iterator& iterator,
	                          vector<LexerToken*>::iterator& iteratorEnd);
	~ExpressionParser();
	Node* parse() override;

	OperatorNode* findWithHighestWeight(vector<OperatorNode*>& vector);
};
