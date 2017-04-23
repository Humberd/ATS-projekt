#include "stdafx.h"
#include "ProcedureNodeMock.h"

ProcedureNodeMock::ProcedureNodeMock(int lineNumber) : ProcedureNode(lineNumber, "bar") {
}

ProcedureNodeMock::~ProcedureNodeMock() {
}

void ProcedureNodeMock::addChild(Node* child) {
	//do nothing
}
