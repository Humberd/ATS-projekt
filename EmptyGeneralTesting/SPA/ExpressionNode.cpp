#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(int sourceLineNumber,
                               RangeNumber* rangeOfRequiredChildNodes) : Node(sourceLineNumber, rangeOfRequiredChildNodes) {
}

ExpressionNode::~ExpressionNode() {
}
