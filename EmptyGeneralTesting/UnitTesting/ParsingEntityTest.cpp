#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include "../SPA/ParsingEntity.h"
#include "../SPA/ParserException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

class MockParser: public ParsingEntity {


public:
	MockParser(vector<LexerToken*>::iterator& iterator,
	           vector<LexerToken*>::iterator& iteratorEnd) : ParsingEntity(iterator, iteratorEnd) {
	}

	Node* parse() override {
		return nullptr;
	};
};

TEST_CLASS(ParsingEntityTest) {
	TEST_METHOD(ParsingEntity_getClassName) {
		vector<LexerToken*> tokensList;
		MockParser* mockParser = new MockParser(tokensList.begin(), tokensList.end());

		auto className = mockParser->getClassName();

		Assert::IsTrue(className == "class MockParser");

		delete mockParser;
	}

	TEST_METHOD(ParsingEntity_nextElement_Valid) {
		vector<LexerToken*> tokensList;
		tokensList.push_back(nullptr);

		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		MockParser* mockParser = new MockParser(iterator, iteratorEnd);

		Assert::IsTrue(iterator != iteratorEnd);
		mockParser->nextElement();
		/*Successfully iterated over 1 element*/
		Assert::IsTrue(iterator == iteratorEnd);

		delete mockParser;
	}

	TEST_METHOD(ParsingEntity_nextElement_Invalid_LastElement) {
		vector<LexerToken*> tokensList;
		tokensList.push_back(nullptr);
		auto iterator = tokensList.begin();
		auto iteratorEnd = tokensList.end();

		++iterator;

		MockParser* mockParser = new MockParser(iterator, iteratorEnd);

		Assert::IsTrue(iterator == iteratorEnd);

		auto pointer = [mockParser] {
					mockParser->nextElement();
				};
		Assert::ExpectException<ParserException>(pointer);

		delete mockParser;
	}
};
