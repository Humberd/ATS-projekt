#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QueryEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QueryEvaluatorTest) {
	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_1_ANY) {
		vector<DeclaredVariable*> declaredVariables;
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		Parameter* parameter = new Parameter;
		parameter->setType(ParameterType::ANY);
		parameter->setIntegerValue(15);
		parameter->setStringValue("foobar");
		parameter->setVariableName("myVarName");

		InvokationParam* invokationParam = queryEvaluator->changeParameterToInvokationParam(parameter);

		Assert::IsNotNull(invokationParam);
		Assert::IsTrue(invokationParam->getState() == InvokationParamState::ANY);
		Assert::IsTrue(invokationParam->getValue() == "");
		Assert::IsTrue(invokationParam->getVariableName() == "");

		delete queryEvaluator , parameter;
	}

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_2_VARIABLE) {
		vector<DeclaredVariable*> declaredVariables;
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		Parameter* parameter = new Parameter;
		parameter->setType(ParameterType::VARIABLE);
		parameter->setIntegerValue(15);
		parameter->setStringValue("foobar");
		parameter->setVariableName("myVarName");

		InvokationParam* invokationParam = queryEvaluator->changeParameterToInvokationParam(parameter);

		Assert::IsNotNull(invokationParam);
		Assert::IsTrue(invokationParam->getState() == InvokationParamState::VARIABLE);
		Assert::IsTrue(invokationParam->getValue() == "");
		Assert::IsTrue(invokationParam->getVariableName() == "myVarName");

		delete queryEvaluator , parameter;
	}

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_3_INTEGER) {
		vector<DeclaredVariable*> declaredVariables;
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		Parameter* parameter = new Parameter;
		parameter->setType(ParameterType::INTEGER);
		parameter->setIntegerValue(15);
		parameter->setStringValue("foobar");
		parameter->setVariableName("myVarName");

		InvokationParam* invokationParam = queryEvaluator->changeParameterToInvokationParam(parameter);

		Assert::IsNotNull(invokationParam);
		Assert::IsTrue(invokationParam->getState() == InvokationParamState::VALUE);
		Assert::IsTrue(invokationParam->getValue() == "15");
		Assert::IsTrue(invokationParam->getValueType() == ValueType::INTEGER);
		Assert::IsTrue(invokationParam->getVariableName() == "");

		delete queryEvaluator , parameter;
	}

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_4_STRING) {
		vector<DeclaredVariable*> declaredVariables;
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		Parameter* parameter = new Parameter;
		parameter->setType(ParameterType::STRING);
		parameter->setIntegerValue(15);
		parameter->setStringValue("foobar");
		parameter->setVariableName("myVarName");

		InvokationParam* invokationParam = queryEvaluator->changeParameterToInvokationParam(parameter);

		Assert::IsNotNull(invokationParam);
		Assert::IsTrue(invokationParam->getState() == InvokationParamState::VALUE);
		Assert::IsTrue(invokationParam->getValue() == "foobar");
		Assert::IsTrue(invokationParam->getValueType() == ValueType::STRING);
		Assert::IsTrue(invokationParam->getVariableName() == "");

		delete queryEvaluator , parameter;
	}

	TEST_METHOD(QueryEvaluator_findUniqueEvalResultsFromColumn_1) {
		vector<DeclaredVariable*> declaredVariables;
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		vector<string>* row1 = new vector<string>;
		row1->push_back("1");
		vector<string>* row2 = new vector<string>;
		row2->push_back("1");
		vector<string>* row3 = new vector<string>;
		row3->push_back("4");
		vector<string>* row4 = new vector<string>;
		row4->push_back("5");
		vector<string>* row5 = new vector<string>;
		row5->push_back("1");
		vector<string>* row6 = new vector<string>;
		row6->push_back("1");
		vector<string>* row7 = new vector<string>;
		row7->push_back("v");

		vector<vector<string>*> evalResults = {
			row1,
			row2,
			row3,
			row4,
			row5,
			row6,
			row7,
		};
		queryEvaluator->setEvalResults(evalResults);

		vector<string> uniqueResults = queryEvaluator->findUniqueEvalResultsFromColumn(0);

		Assert::IsTrue(uniqueResults.size() == 4);

		for (vector<string>* evalResult : evalResults) {
			evalResult->clear();
		}
		delete queryEvaluator;
	}
};
