#include "stdafx.h"
#include "ProcedureNodeMock.h"

ProcedureNodeMock::ProcedureNodeMock(int sourceLineNumber,
                                     int programLineNumber) : ProcedureNode(sourceLineNumber, programLineNumber, "bar") {
}

ProcedureNodeMock::~ProcedureNodeMock() {
}

void ProcedureNodeMock::addChild(Node* child) {
	//do nothing
}
