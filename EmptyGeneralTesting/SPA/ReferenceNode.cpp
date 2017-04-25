#include "ReferenceNode.h"
#include <vcruntime_typeinfo.h>
#include "ValidateException.h"
#include "VariableNode.h"

ReferenceNode::ReferenceNode(int sourceLineNumber,
                             int programLineNumber) : ExpressionNode(sourceLineNumber, programLineNumber, new RangeNumber(0, 0)) {
}

ReferenceNode::~ReferenceNode() {
}
