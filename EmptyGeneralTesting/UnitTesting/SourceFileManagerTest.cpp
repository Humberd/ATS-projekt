#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/SourceFileManager.h"
#include "../SPA/SourceFileException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceFileManagerTest) {
	TEST_METHOD(SourceFileManager_readFile_Valid) {
		SourceFileManager* manager = new SourceFileManager("../UnitTesting/TestSource1.txt");
		auto fileLinse = manager->readFile();

		delete manager;
	}

	TEST_METHOD(SourceFileManager_readFile_WrongPath) {
		SourceFileManager* manager = new SourceFileManager("not existing path.txt");

		auto pointer = [manager] {
			manager->readFile();
		};

		Assert::ExpectException<SourceFileException>(pointer);

		delete manager;
	}
};