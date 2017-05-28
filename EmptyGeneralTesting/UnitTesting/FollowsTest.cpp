#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/SourceFileManager.h"
#include "../SPA/Lexer.h"
#include "../SPA/SourceParser.h"
#include "../SPA/ProgramLineEvaluator.h"
#include "../SPA/Follows.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(FollowsTest) {

	TEST_METHOD(FollowsTestTestMethod) {
		vector<int> t1;
		vector<int> t2;
		vector<int> t3;
		vector<int> t4;
		vector<int> t5;
		vector<int> t6;
		vector<int> t7;
		vector<int> t8;
		vector<int> t9;
		vector<int> t10;
		vector<int> t11;
		vector<int> t12;
		vector<int> t13;
		vector<int> t14;
		vector<int> t15;
		vector<int> t16;
		vector<int> t17;
		t1.push_back(2);
		t2.push_back(3);
		t3.push_back(4);
		t4.push_back(5);
		t5.push_back(6);
		t6.push_back(7);
		t7.push_back(8);
		t8.push_back(9);
		t9.push_back(18);
		t10.push_back(11);
		t11.push_back(14);
		t12.push_back(13);
		//t13.push_back(15);
		t14.push_back(15);
		t15.push_back(16);
		t16.push_back(17);
		//t17.push_back(16);


		map<int, vector<int>> mapa;
		mapa[1] = t1;
		mapa[2] = t2;
		mapa[3] = t3;
		mapa[4] = t4;
		mapa[5] = t5;
		mapa[6] = t6;
		mapa[7] = t7;
		mapa[8] = t8;
		mapa[9] = t9;
		mapa[10] = t10;
		mapa[11] = t11;
		mapa[12] = t12;
		mapa[13] = t13;
		mapa[14] = t14;
		mapa[15] = t15;
		mapa[16] = t16;
		mapa[17] = t17;
		Follows* follows;
		follows = follows->getInstance(mapa);
 		vector<STMT*> test = follows->getFollows(new STMT(11), false);
		vector<STMT*> test3 = follows->getFollows(new STMT(10), false);
		vector<STMT*> test2 = follows->getFollows(new STMT(4), true);

		vector<STMT*> test4 = follows->getFollowsByWithoutDeep(new STMT(10));
		vector<STMT*> test5= follows->getFollowsByWithDeep(new STMT(4));

		bool test6 = follows->isFollows(new STMT(10), new STMT(11),false);
		bool test7 = follows->isFollows(new STMT(2), new STMT(3), false);
		bool test8 = follows->isFollows(new STMT(2), new STMT(4), true);


		bool test9 = follows->isFollowsBy(new STMT(11), new STMT(10), false);
		bool test10 = follows->isFollowsBy(new STMT(3), new STMT(2), false);
		bool test11 = follows->isFollowsBy(new STMT(4), new STMT(2), true);

	}

};