#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/QueryEvaluator.h"
#include "../SPA/DeclarationKeywords.h"
#include "../SPA/PkbBridgeMockImpl.h"
#include "../SPA/QueryEvaluatorException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QueryEvaluatorTest2) {
	vector<MethodEvaluatorResponse*> responses;
	vector<vector<string>*> oldState;
	vector<vector<string>*> newState;
	vector<string> columnVariableNames;
	QueryEvaluator* queryEvaluator;
	PkbBrigde* pkBBridge = new PkbBridgeMockImpl;
	bool booleanResult;


	TEST_METHOD_INITIALIZE(Init) {
		this->queryEvaluator = new QueryEvaluator;
		this->queryEvaluator->setPkbBrigde(pkBBridge);
		booleanResult = true;
	}

	TEST_METHOD_CLEANUP(Destruct) {
		for (auto res : responses) {
			delete res;
		}
		responses.clear();
		for (vector<string>* o1 : oldState) {
			o1->clear();
			delete o1;
		}
		oldState.clear();
		for (vector<string>* o1 : newState) {
			o1->clear();
			delete o1;
		}
		newState.clear();
		delete queryEvaluator;
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_1_booleanResponseToTrue) {
		MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(true);
		responses.push_back(response);

		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);

		Assert::IsTrue(booleanResult);
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_2_booleanResponseToFalse) {
		MethodEvaluatorResponse* response = new MethodEvaluatorResponse;
		response->setState(ResponseState::BOOLEAN);
		response->setBooleanResponse(false);
		responses.push_back(response);

		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);


		Assert::IsFalse(booleanResult);
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_3_OneFalseOneTrueBooleanResponse) {
		MethodEvaluatorResponse* response1 = new MethodEvaluatorResponse;
		response1->setState(ResponseState::BOOLEAN);
		response1->setBooleanResponse(true);
		responses.push_back(response1);
		MethodEvaluatorResponse* response2 = new MethodEvaluatorResponse;
		response2->setState(ResponseState::BOOLEAN);
		response2->setBooleanResponse(false);
		responses.push_back(response2);

		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);

		Assert::IsFalse(booleanResult);
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_4_OneTrueOneFalseBooleanResponse) {
		MethodEvaluatorResponse* response1 = new MethodEvaluatorResponse;
		response1->setState(ResponseState::BOOLEAN);
		response1->setBooleanResponse(false);
		responses.push_back(response1);
		MethodEvaluatorResponse* response2 = new MethodEvaluatorResponse;
		response2->setState(ResponseState::BOOLEAN);
		response2->setBooleanResponse(true);
		responses.push_back(response2);

		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);

		Assert::IsFalse(booleanResult);
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_5_vectorResponse) {
		MethodEvaluatorResponse* response1 = new MethodEvaluatorResponse;
		response1->setState(ResponseState::VECTOR);
		response1->setVariableName("a");
		response1->setVariableType("assign");
		response1->setInsertToColumnName("");
		vector<string> vectorResponse = {"8","9","10","11"};
		response1->setVectorResponse(vectorResponse);
		responses.push_back(response1);

		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);

		Assert::IsTrue(oldState.size() == 0);
		Assert::IsTrue(newState.size() == 4);
		Assert::IsTrue(newState.at(0)->at(0) == "8");
		Assert::IsTrue(newState.at(1)->at(0) == "9");
		Assert::IsTrue(newState.at(2)->at(0) == "10");
		Assert::IsTrue(newState.at(3)->at(0) == "11");
		Assert::IsTrue(columnVariableNames.size() == 1);
		Assert::IsTrue(columnVariableNames.at(0) == "a");
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_6_vectorResponseWithExistingResults) {
		MethodEvaluatorResponse* response1 = new MethodEvaluatorResponse;
		response1->setState(ResponseState::VECTOR);
		response1->setVariableName("a");
		response1->setVariableType("assign");
		response1->setInsertToColumnName("s");
		response1->setInsertToColumnValue("1");
		vector<string> vectorResponse = {"8","9","10","11"};
		response1->setVectorResponse(vectorResponse);
		responses.push_back(response1);

		columnVariableNames.push_back("s");
		oldState.push_back(new vector<string>{"1"});


		queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);

		Assert::IsTrue(oldState.size() == 1);
		Assert::IsTrue(newState.size() == 4);
		Assert::IsTrue(newState.at(0)->at(0) == "1");
		Assert::IsTrue(newState.at(0)->at(1) == "8");
		Assert::IsTrue(newState.at(1)->at(0) == "1");
		Assert::IsTrue(newState.at(1)->at(1) == "9");
		Assert::IsTrue(newState.at(2)->at(0) == "1");
		Assert::IsTrue(newState.at(2)->at(1) == "10");
		Assert::IsTrue(newState.at(3)->at(0) == "1");
		Assert::IsTrue(newState.at(3)->at(1) == "11");
		Assert::IsTrue(columnVariableNames.size() == 2);
		Assert::IsTrue(columnVariableNames.at(0) == "s");
		Assert::IsTrue(columnVariableNames.at(1) == "a");
	}

	TEST_METHOD(QueryEvaluator_changeResultsStateBasedOnResponses_Valid_7_vectorResponseWithExistingResultsButInsertToColumnNameDoesntMatch) {
		MethodEvaluatorResponse* response1 = new MethodEvaluatorResponse;
		response1->setState(ResponseState::VECTOR);
		response1->setVariableName("a");
		response1->setVariableType("assign");
		response1->setInsertToColumnName("c"); //wants to insert to column c, but declared columnVariableNames has only "s"
		response1->setInsertToColumnValue("1");
		vector<string> vectorResponse = {"8","9","10","11"};
		response1->setVectorResponse(vectorResponse);
		responses.push_back(response1);

		columnVariableNames.push_back("s");
		oldState.push_back(new vector<string>{"1"});

		auto pointer = [this]() {
					queryEvaluator->changeResultsStateBasedOnResponses(responses, oldState, newState, booleanResult, columnVariableNames);
				};

		Assert::ExpectException<QueryEvaluatorException>(pointer);
	}
};
