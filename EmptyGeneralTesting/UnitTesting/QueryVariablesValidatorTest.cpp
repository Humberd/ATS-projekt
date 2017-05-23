#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/DeclaredVariable.h"
#include "../SPA/QueryVariablesValidator.h"
#include "../SPA/QueryVariablesValidatorException.h"
#include "../SPA/DeclarationKeywords.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(QueryVariablesValidatorTest) {
	TEST_METHOD(QueryVariablesValidator_doesVariableExist_Valid) {
		vector<string> varNames = {"a", "b", "s", "foo", "Grazyna"};
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable("", "a"),
			new DeclaredVariable("", "s"),
			new DeclaredVariable("", "Grazyna"),
			new DeclaredVariable("", "foo"),
			new DeclaredVariable("", "b")
		};

		QueryVariablesValidator* validator = new QueryVariablesValidator;

		for (auto varName : varNames) {
			Assert::IsTrue(validator->doesVariableExist(varName, declaredVariables));
		}


		varNames.clear();
		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator;
	}

	TEST_METHOD(QueryVariablesValidator_doesVariableExist_Invalid) {
		vector<string> varNames = {"Jeszcze","Polska","Nie","Zginela","Kiedy","My","Zyjemy"};
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable("", "a"),
			new DeclaredVariable("", "s"),
			new DeclaredVariable("", "Grazyna"),
			new DeclaredVariable("", "foo"),
			new DeclaredVariable("", "b")
		};

		QueryVariablesValidator* validator = new QueryVariablesValidator;

		for (auto varName : varNames) {
			Assert::IsFalse(validator->doesVariableExist(varName, declaredVariables));
		}


		varNames.clear();
		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator;
	}

	TEST_METHOD(QueryVariablesValidator_checkIfVariablesWereDeclared_Valid) {
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable("", "a"),
			new DeclaredVariable("", "s"),
			new DeclaredVariable("", "Grazyna"),
			new DeclaredVariable("", "foo"),
			new DeclaredVariable("", "b")
		};

		QueryRequest* queryRequest = new QueryRequest;

		ReturnRequest* returnRequest = new ReturnRequest;
		returnRequest->setReturnType(ReturnType::VARIABLES);
		vector<QueryVariable*> returnRequestVariables = {
			new QueryVariable("a", ""),
			new QueryVariable("s", ""),
		};
		returnRequest->setVariables(returnRequestVariables);
		queryRequest->setReturnRequest(returnRequest);

		vector<MethodRequest*> methodRequests;
		MethodRequest* methodRequest = new MethodRequest;
		Parameter* leftParam = new Parameter;
		leftParam->setType(ParameterType::VARIABLE);
		leftParam->setVariableName("foo");
		methodRequest->setLeftParam(leftParam);
		Parameter* rightParam = new Parameter;
		rightParam->setType(ParameterType::VARIABLE);
		rightParam->setVariableName("Grazyna");
		methodRequest->setRightParam(rightParam);
		methodRequests.push_back(methodRequest);
		queryRequest->setMethodRequests(methodRequests);

		vector<WithRequest*> withRequests;
		WithRequest* withRequest = new WithRequest;
		withRequest->setType(WithType::VARIABLE);
		withRequest->setLeftSideVariable(new QueryVariable("a", ""));
		withRequest->setRightSideVariable(new QueryVariable("s", ""));
		withRequests.push_back(withRequest);
		queryRequest->setWithRequests(withRequests);


		QueryVariablesValidator* validator = new QueryVariablesValidator;
		validator->checkIfVariablesWereDeclared(declaredVariables, queryRequest);


		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator , queryRequest;
	}

	TEST_METHOD(QueryVariablesValidator_checkIfVariablesWereDeclared_Invalid) {
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable("", "a"),
			new DeclaredVariable("", "s"),
			new DeclaredVariable("", "Grazyna"),
			new DeclaredVariable("", "foo"),
			new DeclaredVariable("", "b")
		};

		QueryRequest* queryRequest = new QueryRequest;

		ReturnRequest* returnRequest = new ReturnRequest;
		returnRequest->setReturnType(ReturnType::VARIABLES);
		vector<QueryVariable*> returnRequestVariables = {
			new QueryVariable("a", ""),
			new QueryVariable("s", ""),
		};
		returnRequest->setVariables(returnRequestVariables);
		queryRequest->setReturnRequest(returnRequest);

		vector<MethodRequest*> methodRequests;
		MethodRequest* methodRequest = new MethodRequest;
		Parameter* leftParam = new Parameter;
		leftParam->setType(ParameterType::VARIABLE);
		leftParam->setVariableName("foo");
		methodRequest->setLeftParam(leftParam);
		Parameter* rightParam = new Parameter;
		rightParam->setType(ParameterType::VARIABLE);
		rightParam->setVariableName("Grazyna");
		methodRequest->setRightParam(rightParam);
		methodRequests.push_back(methodRequest);
		queryRequest->setMethodRequests(methodRequests);

		vector<WithRequest*> withRequests;
		WithRequest* withRequest = new WithRequest;
		withRequest->setType(WithType::VARIABLE);
		withRequest->setLeftSideVariable(new QueryVariable("a", ""));
		withRequest->setRightSideVariable(new QueryVariable("v", ""));//not declared variable
		withRequests.push_back(withRequest);
		queryRequest->setWithRequests(withRequests);


		QueryVariablesValidator* validator = new QueryVariablesValidator;

		auto pointer = [validator, declaredVariables, queryRequest]() {
					validator->checkIfVariablesWereDeclared(declaredVariables, queryRequest);
				};

		Assert::ExpectException<QueryVariablesValidatorException>(pointer);

		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator , queryRequest;
	}

	TEST_METHOD(QueryVariablesValidator_getVariableType_Valid) {
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable(DeclarationKeywords::ASSIGN, "a"),
			new DeclaredVariable(DeclarationKeywords::STATEMENT, "s"),
			new DeclaredVariable(DeclarationKeywords::PROCEDURE, "Grazyna"),
			new DeclaredVariable(DeclarationKeywords::IF, "f"),
			new DeclaredVariable(DeclarationKeywords::WHILE, "w")
		};

		QueryVariablesValidator* validator = new QueryVariablesValidator;

		for (auto variable : declaredVariables) {
			string foundVarType = validator->getVariableType(variable->getName(), declaredVariables);
			Assert::IsTrue(foundVarType == variable->getType());
		}


		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator;
	}

	TEST_METHOD(QueryVariablesValidator_checkIfVariablesHaveValidProperties_Valid) {
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable(DeclarationKeywords::ASSIGN, "a"),
			new DeclaredVariable(DeclarationKeywords::STATEMENT, "s"),
			new DeclaredVariable(DeclarationKeywords::PROCEDURE, "Grazyna"),
			new DeclaredVariable(DeclarationKeywords::IF, "foo"),
			new DeclaredVariable(DeclarationKeywords::WHILE, "b")
		};

		QueryRequest* queryRequest = new QueryRequest;

		ReturnRequest* returnRequest = new ReturnRequest;
		returnRequest->setReturnType(ReturnType::VARIABLES);
		vector<QueryVariable*> returnRequestVariables = {
			new QueryVariable("a", ""),
			new QueryVariable("s", "stmt"),
		};
		returnRequest->setVariables(returnRequestVariables);
		queryRequest->setReturnRequest(returnRequest);

		vector<MethodRequest*> methodRequests;
		MethodRequest* methodRequest = new MethodRequest;
		Parameter* leftParam = new Parameter;
		leftParam->setType(ParameterType::VARIABLE);
		leftParam->setVariableName("foo");
		methodRequest->setLeftParam(leftParam);
		Parameter* rightParam = new Parameter;
		rightParam->setType(ParameterType::VARIABLE);
		rightParam->setVariableName("Grazyna");
		methodRequest->setRightParam(rightParam);
		methodRequests.push_back(methodRequest);
		queryRequest->setMethodRequests(methodRequests);

		vector<WithRequest*> withRequests;
		WithRequest* withRequest = new WithRequest;
		withRequest->setType(WithType::VARIABLE);
		withRequest->setLeftSideVariable(new QueryVariable("Grazyna", "procName"));
		withRequest->setRightSideVariable(new QueryVariable("s", "stmt"));
		withRequests.push_back(withRequest);
		queryRequest->setWithRequests(withRequests);


		QueryVariablesValidator* validator = new QueryVariablesValidator;
		validator->checkIfVariablesHaveValidProperties(declaredVariables, queryRequest);


		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator , queryRequest;
	}

	TEST_METHOD(QueryVariablesValidator_checkIfVariablesHaveValidProperties_Invalid) {
		vector<DeclaredVariable*> declaredVariables = {
			new DeclaredVariable(DeclarationKeywords::ASSIGN, "a"),
			new DeclaredVariable(DeclarationKeywords::STATEMENT, "s"),
			new DeclaredVariable(DeclarationKeywords::PROCEDURE, "Grazyna"),
			new DeclaredVariable(DeclarationKeywords::IF, "foo"),
			new DeclaredVariable(DeclarationKeywords::WHILE, "b")
		};

		QueryRequest* queryRequest = new QueryRequest;

		ReturnRequest* returnRequest = new ReturnRequest;
		returnRequest->setReturnType(ReturnType::VARIABLES);
		vector<QueryVariable*> returnRequestVariables = {
			new QueryVariable("a", ""),
			new QueryVariable("s", "stmt"),
		};
		returnRequest->setVariables(returnRequestVariables);
		queryRequest->setReturnRequest(returnRequest);

		vector<MethodRequest*> methodRequests;
		MethodRequest* methodRequest = new MethodRequest;
		Parameter* leftParam = new Parameter;
		leftParam->setType(ParameterType::VARIABLE);
		leftParam->setVariableName("foo");
		methodRequest->setLeftParam(leftParam);
		Parameter* rightParam = new Parameter;
		rightParam->setType(ParameterType::VARIABLE);
		rightParam->setVariableName("Grazyna");
		methodRequest->setRightParam(rightParam);
		methodRequests.push_back(methodRequest);
		queryRequest->setMethodRequests(methodRequests);

		vector<WithRequest*> withRequests;
		WithRequest* withRequest = new WithRequest;
		withRequest->setType(WithType::VARIABLE);
		withRequest->setLeftSideVariable(new QueryVariable("Grazyna", "procName"));
		withRequest->setRightSideVariable(new QueryVariable("s", "procName"));//should be stmt
		withRequests.push_back(withRequest);
		queryRequest->setWithRequests(withRequests);


		QueryVariablesValidator* validator = new QueryVariablesValidator;

		auto pointer = [validator, declaredVariables, queryRequest]() {
					validator->checkIfVariablesHaveValidProperties(declaredVariables, queryRequest);
				};

		Assert::ExpectException<QueryVariablesValidatorException>(pointer);

		for (auto declaredVariable : declaredVariables) {
			delete declaredVariable;
		}
		declaredVariables.clear();

		delete validator , queryRequest;
	}
};
