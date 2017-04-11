#include "stdafx.h"
#include <CppUnitTest.h>
#include "../AutoTester/QueryParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
TEST_CLASS(QueryParserTest) 
{
	TEST_METHOD(QueryParser_ReadFile) 
	{
		QueryParser* queryParser = new QueryParser;
		vector<vector<string>> dupa=queryParser->ReadFile("text.txt");
		//vector<PROC> result = calls->getCalls("1", true);

		Assert::IsTrue(2 == 2);

		//		for (auto item : result) {
		//			string foo = dynamic_cast<string&>(item);
		//			Logger::WriteMessage(foo.c_str());
		//		}

		delete queryParser;
	}
};