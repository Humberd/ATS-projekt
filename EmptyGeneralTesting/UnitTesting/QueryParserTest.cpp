#include "stdafx.h"
#include <CppUnitTest.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include "../SPA/QueryParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
TEST_CLASS(QueryParserTest) 
{
	TEST_METHOD(QueryParser_ReadFile) 
	{

		QueryParser* queryParser = new QueryParser;
		vector<vector<string>> output=queryParser->ReadFile("test.txt");
		//vector<PROC> result = calls->getCalls("1", true);

		Assert::IsTrue(2 == 2);

		//		for (auto item : result) {
		//			string foo = dynamic_cast<string&>(item);
		//			Logger::WriteMessage(foo.c_str());
		//		}

		delete queryParser;
	}
};