#include "stdafx.h"
#include <CppUnitTestAssert.h>
#include <vector>
#include "../SPA/LexerToken.h"
#include "../SPA/SourceParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceParserTest) {
	TEST_METHOD(SourceParser_constructor_Valid) {
		vector<LexerToken*> tokensList;
		SourceParser* parser = new SourceParser(tokensList);

		/*Just check if the object was created successfully*/

		delete parser;
	}
};
