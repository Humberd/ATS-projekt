#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/Spa.h"
#include "../SPA/StatementsFilter.h"
#include "../SPA/ResponseParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(LiveTests) {
	string declaredVariables = "";
	string expresssion = "";
	string expectedResult = "";

	Node* rootNode = Spa::generateAstFromFile("../IntegrationTesting/final-source.txt");
	SpaDataContainer* spaDataContainer = Spa::generateHelperTables(rootNode);

	TEST_METHOD_CLEANUP(Eval) {
		list<string> result = Spa::evaluateExpression(declaredVariables, expresssion, spaDataContainer);
		string parsedResult = ResponseParser::parseForTestingPurposes(result);

		Assert::IsTrue(parsedResult == expectedResult, wstring(parsedResult.begin(), parsedResult.end()).c_str());
	}

	TEST_METHOD(Test_1) {
		declaredVariables = "variable v;";
		expresssion = "Select v";
		expectedResult = "a,b,c,d,e,i,k,m,x,y,z";
	}

	TEST_METHOD(Test_2) {
		declaredVariables = "stmt s;";
		expresssion = "Select s";
		expectedResult = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74";
	}

	TEST_METHOD(Test_3) {
		declaredVariables = "while w;";
		expresssion = "Select w";
		expectedResult = "5,15,21,26,41,48,51,52,69";
	}

	TEST_METHOD(Test_4) {
		declaredVariables = "if i;";
		expresssion = "Select i";
		expectedResult = "4,12,18,29,33,34,57,63,64,65,71";
	}

	TEST_METHOD(Test_5) {
		declaredVariables = "call c;";
		expresssion = "Select c";
		expectedResult = "3,10,36,50,56";
	}

	TEST_METHOD(Test_6) {
		declaredVariables = "assign a;";
		expresssion = "Select a";
		expectedResult = "1,2,6,7,8,9,11,13,14,16,17,19,20,22,23,24,25,27,28,30,31,32,35,37,38,39,40,42,43,44,45,46,47,49,53,54,55,58,59,60,61,62,66,67,68,70,72,73,74";
	}

	TEST_METHOD(Test_7) {
		declaredVariables = "procedure p;";
		expresssion = "Select p";
		expectedResult = "a,d,p,q";
	}

	TEST_METHOD(Test_8) {
		declaredVariables = "procedure p;";
		expresssion = "Select p.procName";
		expectedResult = "a,d,p,q";
	}

	TEST_METHOD(Test_9) {
		declaredVariables = "call c;";
		expresssion = "Select c.procName";
		expectedResult = "a,d,q";
	}

	TEST_METHOD(Test_10) {
		declaredVariables = "constant c;";
		expresssion = "Select c";
		expectedResult = "1,2,3,5,8";
	}

	TEST_METHOD(Test_11) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent(s, 11)";
		expectedResult = "4";
	}

	TEST_METHOD(Test_12) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent(15, s)";
		expectedResult = "16,17,18,45";
	}

	TEST_METHOD(Test_13) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Parent(4, a)";
		expectedResult = "8,9,11";
	}

	TEST_METHOD(Test_14) {
		declaredVariables = "call c;";
		expresssion = "Select c such that Parent(4, c)";
		expectedResult = "10";
	}

	TEST_METHOD(Test_15) {
		declaredVariables = "if i;";
		expresssion = "Select i such that Parent(4, i)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_16) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent*(s, 28)";
		expectedResult = "26,21,18,15,12";
	}

	TEST_METHOD(Test_17) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Parent*(12, a)";
		expectedResult = "13,14,16,17,19,20,22,23,24,25,27,28,30,31,32,35,37,38,39,40,42,43,44,45,46,47,49";
	}

	TEST_METHOD(Test_18) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent*(s, 5)";
		expectedResult = "4";
	}

	TEST_METHOD(Test_19) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent*(8, s)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_20) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Parent*(s, 1)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_21) {
		declaredVariables = "stmt s;";
		expresssion = "Select BOOLEAN such that Parent(s,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_22) {
		declaredVariables = "stmt s;";
		expresssion = "Select BOOLEAN such that Parent*(s,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_23) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent(_,foo)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_24) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent*(_,foo)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_25) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent(_,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_26) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent(1,9)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_27) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent(63,66)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_28) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent*(63,66)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_29) {
		declaredVariables = "stmt foo;";
		expresssion = "Select foo such that Parent*(foo,foo)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_30) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Parent(foo,foo)";
		expectedResult = "false";
	}


	//	TEST_METHOD(Test_171) {
	//		declaredVariables = "assign a; stmt s;";
	//		expresssion = "Select s with a.stmt# = s.stmt#";
	//		expectedResult = "1,2,6,7,8,9,11,13,14,16,17,19,20,22,23,24,25,27,28,30,31,32,35,37,38,39,40,42,43,44,45,46,47,49,53,54,55,58,59,60,61,62,66,67,68,70,72,73,74";
	//	}
};
