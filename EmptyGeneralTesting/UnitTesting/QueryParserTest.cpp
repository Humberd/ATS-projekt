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

		std::string str = "dfdffd";

		if (std::find_if(str.begin(), str.end(), isdigit) != str.end())
		{
			int b = 4;
			//std::cout << "No digits allowed in name\n";
		}


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