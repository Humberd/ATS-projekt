#include "stdafx.h"
#include "ProcedureNodeMock.h"

ProcedureNodeMock::ProcedureNodeMock(int sourceLineNumber) : ProcedureNode(sourceLineNumber, "bar") {
}

ProcedureNodeMock::~ProcedureNodeMock() {
}

void ProcedureNodeMock::addChild(Node* child) {
	//do nothing
}
