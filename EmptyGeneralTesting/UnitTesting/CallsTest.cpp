#include "stdafx.h"
#include <CppUnitTest.h>
#include "../SPA/Calls.h"
#include "../SPA/Node.h"
#include "../SPA/Spa.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(CallsTest) {
	Node* rootNode = nullptr;

	TEST_METHOD_INITIALIZE(Init) {
		rootNode = Spa::generateAstFromFile("../IntegrationTesting/NextTest.txt");
	}

	TEST_METHOD_CLEANUP(Cleanup) {
		delete rootNode;
	}
	//TEST_METHOD(Calls_getCallsDeep) {
	//	Calls* calls = new Calls;
	//	calls->setCalls(new PROC("1"), new PROC("2"));
	//	calls->setCalls(new PROC("2"), new PROC("3"));

	//	vector<PROC*> result = calls->getCalls(new PROC("1"), true);

	//	Assert::IsTrue(2 == result.size());

	//		//		for (auto item : result) {
	//		//			string foo = dynamic_cast<string&>(item);
	//		//			Logger::WriteMessage(foo.c_str());
	//		//		}

	//	delete calls;
	//}

//
//	TEST_METHOD(Calls_getCallsDeep2) {
//		Calls* calls = new Calls;
//		calls->setCalls(new PROC("1"), new PROC("2"));
//		calls->setCalls(new PROC("2"), new PROC("1"));
//
//		vector<PROC*> result = calls->getCalls(new PROC("1"), true);
//
//		Assert::IsTrue(2 == result.size());
//
//		//		for (auto item : result) {
//		//			string foo = dynamic_cast<string&>(item);
//		//			Logger::WriteMessage(foo.c_str());
//		//		}
//
//		delete calls;
//	}
//
//	TEST_METHOD(Calls_getCallsDeep3) {
//		Calls* calls = new Calls;
//		calls->setCalls(new PROC("1"), new PROC("2"));
//
//		calls->setCalls(new PROC("2"), new PROC("1"));
//
//		calls->setCalls(new PROC("3"), new PROC("4"));
//		calls->setCalls(new PROC("3"), new PROC("5"));
//
//		calls->setCalls(new PROC("4"), new PROC("2"));
//
//		calls->setCalls(new PROC("5"), new PROC("3"));
//		calls->setCalls(new PROC("5"), new PROC("2"));
//
//		Assert::IsTrue(2 == calls->getCalls(new PROC("1"), true).size());
//		Assert::IsTrue(2 == calls->getCalls(new PROC("2"), true).size());
//		Assert::IsTrue(5 == calls->getCalls(new PROC("3"), true).size());
//		Assert::IsTrue(2 == calls->getCalls(new PROC("4"), true).size());
//		Assert::IsTrue(5 == calls->getCalls(new PROC("5"), true).size());
//
//		delete calls;
//	}
//
	TEST_METHOD(setCalls) {
		SpaDataContainer* container = Spa::generateHelperTables(rootNode);

		Calls *calls = new Calls(container->callsTable);
		
		PROC* p = new PROC("1");
		PROC* q = new PROC("2");

		calls->setCalls(p, q);
		bool a = calls->isCalls(p->getProc(), q);

		Assert::IsTrue(calls->isCalls(p->getProc(), q));
		delete calls;
	}

	TEST_METHOD(getCalls) {
		SpaDataContainer* container = Spa::generateHelperTables(rootNode);

		Calls *calls = new Calls(container->callsTable);

		PROC* p0 = new PROC("1");
		PROC* p1 = new PROC("5");
		PROC* p2 = new PROC("6");
		PROC* p3 = new PROC("8");
		PROC* p4 = new PROC("7");

		calls->setCalls(new PROC("1"), new PROC("1"));
		calls->setCalls(new PROC("1"), new PROC("5"));
		calls->setCalls(new PROC("1"), new PROC("6"));

		calls->setCalls(new PROC("2"), new PROC("1"));
		calls->setCalls(new PROC("2"), new PROC("5"));
		calls->setCalls(new PROC("2"), new PROC("6"));
		calls->setCalls(new PROC("2"), new PROC("8"));
		calls->setCalls(new PROC("2"), new PROC("7"));

		calls->setCalls(new PROC("3"), new PROC("4"));
		calls->setCalls(new PROC("3"), new PROC("5"));
		calls->setCalls(new PROC("3"), new PROC("3"));
		calls->setCalls(new PROC("3"), new PROC("4"));

		vector<PROC*> callsList = calls->getCalls(new PROC("2"), false);

		Assert::AreEqual(p0->getProc(), callsList[0]->getProc());
		Assert::AreEqual(p1->getProc(), callsList[1]->getProc());
		Assert::AreEqual(p2->getProc(), callsList[2]->getProc());
		Assert::AreEqual(p3->getProc(), callsList[3]->getProc());
		Assert::AreEqual(p4->getProc(), callsList[4]->getProc());

		delete calls;
	}

	
		TEST_METHOD(getCallsFrom) {
			SpaDataContainer* container = Spa::generateHelperTables(rootNode);

			Calls *calls = new Calls(container->callsTable);
	
			PROC* p0 = new PROC("1");
			PROC* p1 = new PROC("2");
	
			calls->setCalls(new PROC("1"), new PROC("1"));
			calls->setCalls(new PROC("1"), new PROC("5"));
			calls->setCalls(new PROC("1"), new PROC("6"));
			calls->setCalls(new PROC("1"), new PROC("3"));

			calls->setCalls(new PROC("2"), new PROC("1"));
			calls->setCalls(new PROC("2"), new PROC("5"));
			calls->setCalls(new PROC("2"), new PROC("6"));
			calls->setCalls(new PROC("2"), new PROC("8"));
			calls->setCalls(new PROC("2"), new PROC("7"));
			calls->setCalls(new PROC("2"), new PROC("3"));

			calls->setCalls(new PROC("3"), new PROC("4"));
			calls->setCalls(new PROC("3"), new PROC("5"));
			calls->setCalls(new PROC("3"), new PROC("4"));
	
			vector<PROC*> callsList = calls->getCallsFrom(new PROC("3"), false);
	
			Assert::AreEqual(p0->getProc(), callsList[0]->getProc());
			Assert::AreEqual(p1->getProc(), callsList[1]->getProc());
	
			delete calls;
		}

		TEST_METHOD(getCallsFromDeep) {
			SpaDataContainer* container = Spa::generateHelperTables(rootNode);

			Calls *calls = new Calls(container->callsTable);

			PROC* p0 = new PROC("1");
			PROC* p1 = new PROC("2");

			calls->setCalls(new PROC("1"), new PROC("1"));
			calls->setCalls(new PROC("1"), new PROC("5"));
			calls->setCalls(new PROC("1"), new PROC("6"));
			calls->setCalls(new PROC("1"), new PROC("3"));

			calls->setCalls(new PROC("2"), new PROC("1"));
			calls->setCalls(new PROC("2"), new PROC("5"));
			calls->setCalls(new PROC("2"), new PROC("6"));
			calls->setCalls(new PROC("2"), new PROC("8"));
			calls->setCalls(new PROC("2"), new PROC("7"));
			calls->setCalls(new PROC("2"), new PROC("3"));

			calls->setCalls(new PROC("3"), new PROC("4"));
			calls->setCalls(new PROC("3"), new PROC("5"));
			calls->setCalls(new PROC("3"), new PROC("4"));

			vector<PROC*> callsList = calls->getCallsFrom(new PROC("3"), true);

			//Assert::AreEqual(p0->getProc(), callsList[0]->getProc());
			//Assert::AreEqual(p1->getProc(), callsList[1]->getProc());

			delete calls;
		}
};