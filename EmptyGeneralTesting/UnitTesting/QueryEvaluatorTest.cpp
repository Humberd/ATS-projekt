#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QueryEvaluator.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/QueryEvaluatorException.h"
#include "../SPA/PkbBridgeMockImpl.h"

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

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_Valid_2_VARIABLE) {
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

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_Valid_3_INTEGER) {
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

	TEST_METHOD(QueryEvaluator_changeParameterToInvokationParam_Valid_4_STRING) {
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

	TEST_METHOD(QueryEvaluator_findUniqueEvalResultsFromColumn_Valid_1) {
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

	TEST_METHOD(QueryEvaluator_generateParamsIncaseOfAvailableResults_Valid_1) {
		vector<DeclaredVariable*> declaredVariables;
		declaredVariables.push_back(new DeclaredVariable(DeclarationKeywords::ASSIGN, "a"));
		declaredVariables.push_back(new DeclaredVariable(DeclarationKeywords::STATEMENT, "s"));
		declaredVariables.push_back(new DeclaredVariable(DeclarationKeywords::STATEMENT, "g"));
		QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, nullptr);

		vector<string>* row1 = new vector<string>;
		row1->push_back("1");
		row1->push_back("992");
		vector<string>* row2 = new vector<string>;
		row2->push_back("1");
		row2->push_back("23");
		vector<string>* row3 = new vector<string>;
		row3->push_back("4");
		row3->push_back("23");
		vector<string>* row4 = new vector<string>;
		row4->push_back("5");
		row4->push_back("14");
		vector<string>* row5 = new vector<string>;
		row5->push_back("1");
		row5->push_back("443");
		vector<string>* row6 = new vector<string>;
		row6->push_back("1");
		row6->push_back("123");
		vector<string>* row7 = new vector<string>;
		row7->push_back("1");
		row7->push_back("123");

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

		vector<string> columnVariableNames = {"a", "s"};
		queryEvaluator->setColumnVariableNames(columnVariableNames);

		/*-----------*/
		InvokationParam* invokationParam = new InvokationParam;
		invokationParam->setState(InvokationParamState::ANY);

		auto pointer = [invokationParam, queryEvaluator]() {
					queryEvaluator->generateParamsIncaseOfAvailableResults(invokationParam);
				};

		Assert::ExpectException<QueryEvaluatorException>(pointer, wstring(L"Any type '_' was not implemented").c_str());
		delete invokationParam;
		/*-----------*/
		invokationParam = new InvokationParam;
		invokationParam->setState(InvokationParamState::VALUE);

		auto res1 = queryEvaluator->generateParamsIncaseOfAvailableResults(invokationParam);
		Assert::IsTrue(res1.size() == 1);
		Assert::IsTrue(invokationParam == res1.at(0));
		res1.clear();
		delete invokationParam;
		/*-----------*/
		invokationParam = new InvokationParam;
		invokationParam->setState(InvokationParamState::VARIABLE);
		invokationParam->setVariableName("a");

		auto res2 = queryEvaluator->generateParamsIncaseOfAvailableResults(invokationParam);
		Assert::IsTrue(res2.size() == 3);
		Assert::IsTrue(res2.at(0)->getState() == InvokationParamState::VALUE);
		Assert::IsTrue(res2.at(0)->getValue() == "1");
		Assert::IsTrue(res2.at(0)->getValueType() == ValueType::INTEGER);

		Assert::IsTrue(res2.at(1)->getState() == InvokationParamState::VALUE);
		Assert::IsTrue(res2.at(1)->getValue() == "4");
		Assert::IsTrue(res2.at(1)->getValueType() == ValueType::INTEGER);

		Assert::IsTrue(res2.at(2)->getState() == InvokationParamState::VALUE);
		Assert::IsTrue(res2.at(2)->getValue() == "5");
		Assert::IsTrue(res2.at(2)->getValueType() == ValueType::INTEGER);

		for (auto res : res2) {
			delete res;
		}
		res2.clear();
		/*-----------*/
		invokationParam = new InvokationParam;
		invokationParam->setState(InvokationParamState::VARIABLE);
		invokationParam->setVariableName("g");//this variable doesn't exist on evalResults

		auto res3 = queryEvaluator->generateParamsIncaseOfAvailableResults(invokationParam);
		Assert::IsTrue(res3.size() == 1);
		Assert::IsTrue(res3.at(0) == invokationParam);
		/*-----------*/

		for (vector<string>* evalResult : evalResults) {
			evalResult->clear();
		}
		evalResults.clear();
		for (auto variable : declaredVariables) {
			delete variable;
		}
		declaredVariables.clear();
		delete queryEvaluator;
	}

	TEST_METHOD(QueryEvaluator_parentEvaluator_Valid_1_value_variable) {
		PkbBrigde* pkbBrigde = new PkbBridgeMockImpl;

		InvokationParam* leftParam = new InvokationParam;
		leftParam->setState(InvokationParamState::VALUE);

		InvokationParam* rightParam = new InvokationParam;
		rightParam->setState(InvokationParamState::VARIABLE);
		rightParam->setVariableName("foo");

		QueryEvaluator* queryEvaluator = new QueryEvaluator;
		queryEvaluator->setPkbBrigde(pkbBrigde);

		MethodEvaluatorResponse* response = queryEvaluator->parentEvaluator(leftParam, rightParam, false);

		Assert::IsNotNull(response);
		Assert::IsTrue(response->getState() == ResponseState::VECTOR);
		Assert::IsTrue(response->getVectorResponse().size() == 4);
		Assert::IsTrue(response->getVariableName() == "foo");

		delete pkbBrigde , leftParam , rightParam , queryEvaluator , response;
	}

	TEST_METHOD(QueryEvaluator_parentEvaluator_Valid_2_variable_value) {
		PkbBrigde* pkbBrigde = new PkbBridgeMockImpl;

		InvokationParam* leftParam = new InvokationParam;
		leftParam->setState(InvokationParamState::VARIABLE);
		leftParam->setVariableName("bar");

		InvokationParam* rightParam = new InvokationParam;
		rightParam->setState(InvokationParamState::VALUE);

		QueryEvaluator* queryEvaluator = new QueryEvaluator;
		queryEvaluator->setPkbBrigde(pkbBrigde);

		MethodEvaluatorResponse* response = queryEvaluator->parentEvaluator(leftParam, rightParam, false);

		Assert::IsNotNull(response);
		Assert::IsTrue(response->getState() == ResponseState::VECTOR);
		Assert::IsTrue(response->getVectorResponse().size() == 1);
		Assert::IsTrue(response->getVariableName() == "bar");

		delete pkbBrigde , leftParam , rightParam , queryEvaluator , response;
	}

	TEST_METHOD(QueryEvaluator_parentEvaluator_Valid_3_value_value) {
		PkbBrigde* pkbBrigde = new PkbBridgeMockImpl;

		InvokationParam* leftParam = new InvokationParam;
		leftParam->setState(InvokationParamState::VALUE);

		InvokationParam* rightParam = new InvokationParam;
		rightParam->setState(InvokationParamState::VALUE);

		QueryEvaluator* queryEvaluator = new QueryEvaluator;
		queryEvaluator->setPkbBrigde(pkbBrigde);

		MethodEvaluatorResponse* response = queryEvaluator->parentEvaluator(leftParam, rightParam, false);

		Assert::IsNotNull(response);
		Assert::IsTrue(response->getState() == ResponseState::BOOLEAN);
		Assert::IsTrue(response->getBooleanResponse() == true);

		delete pkbBrigde , leftParam , rightParam , queryEvaluator , response;
	}

	TEST_METHOD(QueryEvaluator_parentEvaluator_Invalid_1_any_value) {
		PkbBrigde* pkbBrigde = new PkbBridgeMockImpl;

		InvokationParam* leftParam = new InvokationParam;
		leftParam->setState(InvokationParamState::ANY);

		InvokationParam* rightParam = new InvokationParam;
		rightParam->setState(InvokationParamState::VALUE);

		QueryEvaluator* queryEvaluator = new QueryEvaluator;
		queryEvaluator->setPkbBrigde(pkbBrigde);

		auto pointer = [queryEvaluator, leftParam, rightParam]() {
					queryEvaluator->parentEvaluator(leftParam, rightParam, false);
				};

		Assert::ExpectException<QueryEvaluatorException>(pointer);


		delete pkbBrigde , leftParam , rightParam , queryEvaluator;
	}
};
