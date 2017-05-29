#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/SourceFileManager.h"
#include "../SPA/Lexer.h"
#include "../SPA/SourceParser.h"
#include "../SPA/ProgramLineEvaluator.h"
#include "../SPA/Parent.h"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(ParentTest) {

	TEST_METHOD(ParentTestMethod) {
		SourceFileManager* fileManager = new SourceFileManager("../IntegrationTesting/Source2.txt");
		vector<string> fileLines = fileManager->readFile();

		/*Parsing fileLines to a LexerTokens*/
		vector<LexerToken*> tokensList = Lexer::parse(fileLines);

		/*Starting the actual parser*/
		SourceParser* sourceParser = new SourceParser(tokensList);
		ProgramLineEvaluator* evaluator = new ProgramLineEvaluator;
		try {
			Node* rootNode = sourceParser->parse();
			rootNode->validate();
			evaluator->evaluate(rootNode);

			vector<Node*> allNodes = rootNode->getChildren();


			map<int, vector<Node*>>statementTable;
			for (int i = 0; i < allNodes.size(); i++)
			{
				vector<Node*> helpNodes = allNodes[i]->getChildren();
				for (int j = 0; j < helpNodes.size(); j++)
				{
					allNodes.push_back(helpNodes[j]);
				}
			}
			vector<vector<Node*>> parentTableHelp(allNodes.size() + 1);

			for (int i = 0; i < allNodes.size(); i++)
			{
				int lineNumber = allNodes[i]->getProgramLineNumber();
				if (lineNumber < 0)
					continue;
				vector<Node*> vec = parentTableHelp.at(lineNumber);
				vec.push_back(allNodes[i]);
				parentTableHelp[lineNumber] = vec;
				statementTable[lineNumber] = vec;
			}

			vector<int> t1;
			vector<int> t2;
			vector<int> t3;
			vector<int> t4;
			vector<int> t5;
			vector<int> t6;
			vector<int> t7;
			vector<int> t8;
			vector<int> t9;
			vector<int> t10;
			vector<int> t11;
			vector<int> t12;
			vector<int> t13;
			vector<int> t14;
			vector<int> t15;
			vector<int> t16;
			t9.push_back(10);
			t9.push_back(14);
			t9.push_back(15);
			t9.push_back(16);

			t10.push_back(11);
			t10.push_back(12);
			t10.push_back(13);

			map<int, vector<int>> mapa;
			mapa[1] = t1;
			mapa[2] = t2;
			mapa[3] = t3;
			mapa[4] = t4;
			mapa[5] = t5;
			mapa[6] = t6;
			mapa[7] = t7;
			mapa[8] = t8;
			mapa[9] = t9;
			mapa[10] = t10;
			mapa[11] = t11;
			mapa[12] = t12;
			mapa[13] = t13;
			mapa[14] = t14;
			mapa[15] = t15;
			mapa[16] = t16;

			Parent* parent;
			parent=parent->getInstance(mapa, statementTable);
			parent->getParent(new STMT(12), false);
			parent->getParentOf(new STMT(9), false);

			parent->getParent(new STMT(12), true);
			parent->getParentOf(new STMT(9), true);

		}
		catch (exception& e) {
		}
	}


};