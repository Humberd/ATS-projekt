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

	/*---------------ALL---------------*/
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
	/*---------------PARENT------------------*/
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
		expectedResult = "12,15,18,21,26";
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
	/*-----------FOLLOWS--------------*/
	TEST_METHOD(Test_31) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows(s, 11)";
		expectedResult = "10";
	}
	TEST_METHOD(Test_32) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows(15, s)";
		expectedResult = "46";
	}
	TEST_METHOD(Test_33) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Follows(57, a)";
		expectedResult = "61";
	}
	TEST_METHOD(Test_34) {
		declaredVariables = "call c;";
		expresssion = "Select c such that Follows(55, c)";
		expectedResult = "56";
	}
	TEST_METHOD(Test_35) {
		declaredVariables = "if i;";
		expresssion = "Select i such that Follows(62, i)";
		expectedResult = "63";
	}
	TEST_METHOD(Test_36) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows*(s, 26)";
		expectedResult = "22,23,24,25";
	}
	TEST_METHOD(Test_37) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Follows*(16, a)";
		expectedResult = "17,45";
	}

	TEST_METHOD(Test_38) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows*(s, 12)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_39) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows*(50, s)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_40) {
		declaredVariables = "stmt s;";
		expresssion = "Select s such that Follows*(s, 54)";
		expectedResult = "53";
	}

	TEST_METHOD(Test_41) {
		declaredVariables = "stmt s;";
		expresssion = "Select BOOLEAN such that Follows(s,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_42) {
		declaredVariables = "stmt s;";
		expresssion = "Select BOOLEAN such that Follows*(s,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_43) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows(_,foo)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_44) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows*(_,foo)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_45) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows(_,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_46) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows(14,46)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_47) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows(15,46)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_48) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows*(13,46)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_49) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows*(foo,foo)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_50) {
		declaredVariables = "stmt foo;";
		expresssion = "Select BOOLEAN such that Follows*(foo,foo)";
		expectedResult = "false";
	}
	/*--------------------MODIFIES----------------------*/
	TEST_METHOD(Test_51) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Modifies(11,v)";
		expectedResult = "y";
	}

	TEST_METHOD(Test_52) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Modifies(21,v)";
		expectedResult = "a,b,c,e,x";
	}

	TEST_METHOD(Test_53) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Modifies(12,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_54) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Modifies(13,\"y\")";
		expectedResult = "false";
	}

	TEST_METHOD(Test_55) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Modifies(6,v)";
		expectedResult = "m";
	}

	TEST_METHOD(Test_56) {
		declaredVariables = "variable v;";
		expresssion = "Select v.varName such that Modifies(12,v)";
		expectedResult = "a,b,c,e,i,k,m,x,y";
	}

	TEST_METHOD(Test_57) {
		declaredVariables = "procedure p;";
		expresssion = "Select p such that Modifies(p,\"e\")";
		expectedResult = "a,p,q";
	}

	TEST_METHOD(Test_58) {
		declaredVariables = "call c;";
		expresssion = "Select c such that Modifies(c,_)";
		expectedResult = "3,10,36,50,56";
	}

	TEST_METHOD(Test_59) {
		declaredVariables = "procedure p;";
		expresssion = "Select BOOLEAN such that Modifies(p,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_60) {
		declaredVariables = "stmt s; variable v;";
		expresssion = "Select s such that Modifies(s,v)";
		expectedResult = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74";
	}

	TEST_METHOD(Test_61) {
		declaredVariables = "procedure p; variable v;";
		expresssion = "Select p such that Modifies(p,v)";
		expectedResult = "a,d,p,q";
	}

	TEST_METHOD(Test_62) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Modifies(\"p\",v)";
		expectedResult = "a,b,c,e,i,k,m,x,y";
	}

	TEST_METHOD(Test_63) {
		declaredVariables = "call c;";
		expresssion = "Select c.procName such that Modifies(\"q\",_)";
		expectedResult = "a,d,q";
	}

	TEST_METHOD(Test_64) {
		declaredVariables = "prog_line n;";
		expresssion = "Select n such that Modifies(\"q\",\"x\")";
		expectedResult = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74";
	}

	TEST_METHOD(Test_65) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Modifies(14,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_66) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Modifies(18,\"b\")";
		expectedResult = "true";
	}

	TEST_METHOD(Test_67) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Modifies(\"q\",\"x\")";
		expectedResult = "true";
	}

	TEST_METHOD(Test_68) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Modifies(n,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_69) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Modifies(42,\"x\")";
		expectedResult = "false";
	}

	TEST_METHOD(Test_70) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Modifies(36,\"k\")";
		expectedResult = "true";
	}

	/*---------------USES-------------------*/
	TEST_METHOD(Test_71) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Uses(11,v)";
		expectedResult = "b,x";
	}

	TEST_METHOD(Test_72) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Uses(21,v)";
		expectedResult = "b,c,d,e,x,z";
	}

	TEST_METHOD(Test_73) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Uses(12,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_74) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Uses(13,\"y\")";
		expectedResult = "true";
	}

	TEST_METHOD(Test_75) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Uses(6,v)";
		expectedResult = "m";
	}

	TEST_METHOD(Test_76) {
		declaredVariables = "variable v;";
		expresssion = "Select v.varName such that Uses(12,v)";
		expectedResult = "b,c,d,e,i,k,m,x,y,z";
	}

	TEST_METHOD(Test_77) {
		declaredVariables = "procedure p;";
		expresssion = "Select p such that Uses(p,\"e\")";
		expectedResult = "a,p,q";
	}

	TEST_METHOD(Test_78) {
		declaredVariables = "call c;";
		expresssion = "Select c such that Uses(c,_)";
		expectedResult = "3,10,36,50,56";
	}

	TEST_METHOD(Test_79) {
		declaredVariables = "procedure p;";
		expresssion = "Select BOOLEAN such that Uses(p,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_80) {
		declaredVariables = "stmt s; variable v;";
		expresssion = "Select s such that Uses(s,v)";
		expectedResult = "1,2,3,4,5,6,7,8,9,10,11,12,13,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74";
	}

	TEST_METHOD(Test_81) {
		declaredVariables = "procedure p; variable v;";
		expresssion = "Select p such that Uses(p,v)";
		expectedResult = "a,d,p,q";
	}

	TEST_METHOD(Test_82) {
		declaredVariables = "variable v;";
		expresssion = "Select v such that Uses(\"p\",v)";
		expectedResult = "b,c,d,e,i,k,m,x,y,z";
	}

	TEST_METHOD(Test_83) {
		declaredVariables = "call c;";
		expresssion = "Select c.procName such that Uses(\"q\",_)";
		expectedResult = "a,d,q";
	}

	TEST_METHOD(Test_84) {
		declaredVariables = "prog_line n;";
		expresssion = "Select n such that Uses(\"q\",\"x\")";
		expectedResult = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74";
	}

	TEST_METHOD(Test_85) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Uses(14,_)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_86) {
		declaredVariables = "procedure p;";
		expresssion = "Select BOOLEAN such that Uses(18,\"b\")";
		expectedResult = "true";
	}

	TEST_METHOD(Test_87) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Uses(\"q\",\"x\")";
		expectedResult = "true";
	}

	TEST_METHOD(Test_88) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Uses(n,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_89) {
		declaredVariables = "prog_line n;";
		expresssion = "Select BOOLEAN such that Uses(42,\"lala\")";
		expectedResult = "false";
	}

	TEST_METHOD(Test_90) {
		declaredVariables = "";
		expresssion = "Select BOOLEAN such that Uses(36,\"k\")";
		expectedResult = "true";
	}
	/*--------------NEXT-------------------*/
	/*--------------AFFECTS----------------*/
	TEST_METHOD(Test_111) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (6, a)";
		expectedResult = "6,7,8";
	}

	TEST_METHOD(Test_112) {
		declaredVariables = "assign a; ";
		expresssion = "Select a such that Affects (55, a)";
		expectedResult = "58,59,60";
	}

	TEST_METHOD(Test_113) {
		declaredVariables = "assign a; ";
		expresssion = "Select a such that Affects (14,_)";
		expectedResult = "1,2,6,7,8,9,11,13,14,16,17,19,20,22,23,24,25,27,28,30,31,32,35,37,38,39,40,42,43,44,45,46,47,49,53,54,55,58,59,60,61,62,66,67,68,70,72,73,74";
	}

	TEST_METHOD(Test_114) {
		declaredVariables = "assign a; ";
		expresssion = "Select BOOLEAN such that Affects (17, 49)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_115) {
		declaredVariables = "assign a; ";
		expresssion = "Select a such that Affects (23, 1)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_116) {
		declaredVariables = "assign a; ";
		expresssion = "Select a such that Affects (23, a)";
		expectedResult = "16,19,22,24,27,28,32,45";
	}

	TEST_METHOD(Test_117) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects (62,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_118) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects* (23, a)";
		expectedResult = "16,19,22,24,27,28,32,45,25,31,46,17,20,38,39,23,35,42,44,43";
	}

	TEST_METHOD(Test_119) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects* (53, a)";
		expectedResult = "54,55,58,59,60,61";
	}

	TEST_METHOD(Test_120) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects* (_,_)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_121) {
		declaredVariables = "assign ASSIGN;";
		expresssion = "Select ASSIGN such that Affects* (ASSIGN, 32)";
		expectedResult = "13,14,16,17,20,23,24,25,27,28,30,32,37,3940,43";
	}

	TEST_METHOD(Test_122) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects* (17, a)";
		expectedResult = "16,17,19,20,22,27,31,32,35,38,39,42,43,44,45,46";
	}

	TEST_METHOD(Test_123) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects (9, 11)";
		expectedResult = "false";
	}

	TEST_METHOD(Test_124) {
		declaredVariables = "if i;";
		expresssion = "Select i.stmt# such that Affects (13, 16)";
		expectedResult = "4,12,18,29,33,34,57,63,64,65,71";
	}

	TEST_METHOD(Test_125) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects (17, 19)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_126) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects (20, 27)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_127) {
		declaredVariables = "assign a;";
		expresssion = "Select BOOLEAN such that Affects (_,58)";
		expectedResult = "true";
	}

	TEST_METHOD(Test_128) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 13)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_129) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 72)";
		expectedResult = "72";
	}

	TEST_METHOD(Test_130) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 27)";
		expectedResult = "27,28,23,20";
	}

	TEST_METHOD(Test_131) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 45)";
		expectedResult = "13,17,20,23,27,28,37,39";
	}

	TEST_METHOD(Test_132) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 54)";
		expectedResult = "53";
	}

	TEST_METHOD(Test_133) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (a, 68)";
		expectedResult = "62";
	}

	TEST_METHOD(Test_134) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (6, a)";
		expectedResult = "6,7,8";
	}

	TEST_METHOD(Test_135) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (11, a)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_136) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (24, a)";
		expectedResult = "16,23,25";
	}

	TEST_METHOD(Test_137) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (30, a)";
		expectedResult = "24";
	}

	TEST_METHOD(Test_138) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (74, a)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_139) {
		declaredVariables = "assign a;";
		expresssion = "Select a such that Affects (58, a)";
		expectedResult = "none";
	}

	TEST_METHOD(Test_140) {
		declaredVariables = "assign a;";
		expresssion = "Select c.value such that Affects (a,a)";
		expectedResult = "1,2,3,5,8";
	}



	//	TEST_METHOD(Test_171) {
	//		declaredVariables = "assign a; stmt s;";
	//		expresssion = "Select s with a.stmt# = s.stmt#";
	//		expectedResult = "1,2,6,7,8,9,11,13,14,16,17,19,20,22,23,24,25,27,28,30,31,32,35,37,38,39,40,42,43,44,45,46,47,49,53,54,55,58,59,60,61,62,66,67,68,70,72,73,74";
	//	}
};
