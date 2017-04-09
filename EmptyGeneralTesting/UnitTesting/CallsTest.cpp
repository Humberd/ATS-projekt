#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Calls.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(CallsTest) {
	TEST_METHOD(Calls_getCallsDeep) {
		Calls* calls = new Calls;
		calls->setCalls("1", "2");
		calls->setCalls("2", "3");

		vector<PROC> result = calls->getCalls("1", true);

		Assert::IsTrue(2 == result.size());

		//		for (auto item : result) {
		//			string foo = dynamic_cast<string&>(item);
		//			Logger::WriteMessage(foo.c_str());
		//		}

		delete calls;
	}

	TEST_METHOD(Calls_getCallsDeep2) {
		Calls* calls = new Calls;
		calls->setCalls("1", "2");
		calls->setCalls("2", "1");

		vector<PROC> result = calls->getCalls("1", true);

		Assert::IsTrue(2 == result.size());

		//		for (auto item : result) {
		//			string foo = dynamic_cast<string&>(item);
		//			Logger::WriteMessage(foo.c_str());
		//		}

		delete calls;
	}

	TEST_METHOD(Calls_getCallsDeep3) {
		Calls* calls = new Calls;
		calls->setCalls("1", "2");

		calls->setCalls("2", "1");

		calls->setCalls("3", "4");
		calls->setCalls("3", "5");

		calls->setCalls("4", "2");

		calls->setCalls("5", "3");
		calls->setCalls("5", "2");

		Assert::IsTrue(2 == calls->getCalls("1", true).size());
		Assert::IsTrue(2 == calls->getCalls("2", true).size());
		Assert::IsTrue(5 == calls->getCalls("3", true).size());
		Assert::IsTrue(2 == calls->getCalls("4", true).size());
		Assert::IsTrue(5 == calls->getCalls("5", true).size());

		delete calls;
	}

	TEST_METHOD(setCalls) {
		Calls *calls = new Calls;
		PROC p = "1";
		PROC q = "2";
		calls->setCalls(p, q);
		bool a = calls->isCalls(p, q);

		Assert::IsTrue(calls->isCalls(p, q));
		delete calls;
	}

	TEST_METHOD(getCalls) {
		Calls *calls = new Calls;

		PROC p0 = "1";
		PROC p1 = "5";
		PROC p2 = "6";
		PROC p3 = "8";
		PROC p4 = "7";

		calls->setCalls("1", "1");
		calls->setCalls("1", "5");
		calls->setCalls("1", "6");

		calls->setCalls("2", "1");
		calls->setCalls("2", "5");
		calls->setCalls("2", "6");
		calls->setCalls("2", "8");
		calls->setCalls("2", "7");

		calls->setCalls("3", "4");
		calls->setCalls("3", "5");
		calls->setCalls("3", "3");
		calls->setCalls("3", "4");

		vector<PROC> callsList = calls->getCalls("2", false);

		Assert::AreEqual(p0, callsList[0]);
		Assert::AreEqual(p1, callsList[1]);
		Assert::AreEqual(p2, callsList[2]);
		Assert::AreEqual(p3, callsList[3]);
		Assert::AreEqual(p4, callsList[4]);

		delete calls;
	}
	//
//		TEST_METHOD(getCallsFrom) {
//			Calls *calls = new Calls;
//	
//			PROC p0 = "1";
//			PROC p1 = "2";
//	
//			calls->setCalls("1", "1");
//			calls->setCalls("1", "5");
//			calls->setCalls("1", "6");
//			calls->setCalls("1", "3");
//	
//			calls->setCalls("2", "1");
//			calls->setCalls("2", "5");
//			calls->setCalls("2", "6");
//			calls->setCalls("2", "8");
//			calls->setCalls("2", "7");
//			calls->setCalls("2", "3");
//	
//			calls->setCalls("3", "4");
//			calls->setCalls("3", "5");
//			calls->setCalls("3", "3");
//			calls->setCalls("3", "4");
//	
//			vector<PROC> callsList = calls->getCallsFrom("3", false);
//	
//			Assert::AreEqual(p0, callsList[0]);
//			Assert::AreEqual(p1, callsList[1]);
//	
//			delete calls;
//		}
};