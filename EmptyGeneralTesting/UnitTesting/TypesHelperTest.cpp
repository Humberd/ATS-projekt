#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Node.h"
#include "../SPA/ProgramNode.h"
#include <iostream>
#include "../SPA/ProcedureNode.h"
#include "../SPA/TypesHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTesting {
	TEST_CLASS(TypesHelper) {
public:
	TEST_METHOD(isTypeee) {
		ProgramNode* program_node = new ProgramNode;
		Logger::WriteMessage("Hello");
		Node * node = dynamic_cast<Node*>(program_node);
		ProcedureNode* procedureNode = dynamic_cast<ProcedureNode*>(program_node);

		if (node == nullptr) {
			Logger::WriteMessage("Node is a nullptr");
		}
		if (procedureNode == nullptr) {
			Logger::WriteMessage("procedureNode is a nullptr");
		}

//		isType<ProcedureNode>();
	}
	};
}