#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/SourceFileManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceFileManagerTest) {
	TEST_METHOD(SourceFileManager_init) {
		SourceFileManager* manager = new SourceFileManager("../UnitTesting/TestSource1.txt");
		manager->readFile();

		delete manager;
	}
};