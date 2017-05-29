#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ProgramLineEvaluator.h"
#include "../SPA/ProgramNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ProgramLineEvaluatorTest) {
	TEST_METHOD(ProgramLineEvaluator_evaluate) {
		ProgramLineEvaluator* evaluator = new ProgramLineEvaluator;

		int i = 5;

		evaluator->evaluate(new ProgramNode(1), i);

//		Assert::IsTrue(i == 6);

		delete evaluator;
	}
};