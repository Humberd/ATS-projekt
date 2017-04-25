#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(int sourceLineNumber,
                               int programLineNumber,
                               RangeNumber* rangeOfRequiredChildNodes) : Node(sourceLineNumber, programLineNumber, rangeOfRequiredChildNodes) {
}

ExpressionNode::~ExpressionNode() {
}
