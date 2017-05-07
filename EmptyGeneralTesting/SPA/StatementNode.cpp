#include "StatementNode.h"

StatementNode::StatementNode(int sourceLineNumber,
                             RangeNumber* rangeOfRequiredChildNodes) : Node(sourceLineNumber, rangeOfRequiredChildNodes) {
}

StatementNode::~StatementNode() {
}
