#include "StatementNode.h"

StatementNode::StatementNode(int sourceLineNumber,
                             int programLineNumber,
                             RangeNumber* rangeOfRequiredChildNodes) : Node(sourceLineNumber, programLineNumber, rangeOfRequiredChildNodes) {
}

StatementNode::~StatementNode() {
}
