#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ParsingEntity.h"
#include "../SPA/ParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

class MockParser: public ParsingEntity {

public:
	Node* parseEntity(vector<LexerToken*>::iterator& iterator) override {
		return nullptr;
	};
};

TEST_CLASS(ParsingEntityTest) {
	TEST_METHOD(ParsingEntity_getClassName) {
		MockParser mockParser;

		auto className = mockParser.getClassName();

		Assert::IsTrue(className == "class MockParser");
	}

	TEST_METHOD(ParsingEntity_nextElement_Valid) {
		MockParser mockParser;
		vector<LexerToken*> tokensList;
		tokensList.push_back(nullptr);

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		Assert::IsTrue(iterator != iteratorEnd);
		mockParser.nextElement(iterator);
		/*Successfully iterated over 1 element*/
		Assert::IsTrue(iterator == iteratorEnd);
	}

	TEST_METHOD(ParsingEntity_nextElement_Invalid_LastElement) {
		MockParser mockParser;
		vector<LexerToken*> tokensList;
		tokensList.push_back(nullptr);

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		++iterator;

		Assert::IsTrue(iterator == iteratorEnd);

		mockParser.nextElement(iterator);

		auto pointer = [mockParser, &iterator] {
			mockParser.nextElement(iterator);

		};

		Assert::ExpectException<ParserException>(pointer);
	}

	TEST_METHOD(plusplusIterator) {
		vector<int> myVec;

		auto iterator = myVec.begin();

		try {
			++iterator;
		} catch(exception& e) {
			Logger::WriteMessage("Caught an Exception");
		}
		
	}
};