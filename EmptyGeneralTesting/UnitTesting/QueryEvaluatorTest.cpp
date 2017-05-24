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

		delete queryEvaluator, parameter;
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

		delete queryEvaluator, parameter;
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

		delete queryEvaluator, parameter;
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

		delete queryEvaluator, parameter;
	}
};
