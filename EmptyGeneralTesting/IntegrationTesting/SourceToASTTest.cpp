#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/SourceFileManager.h"
#include "../SPA/Lexer.h"
#include "../SPA/SourceParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceToASTTest) {
	TEST_METHOD(SourceToAST_AssignmentSource) {
		/*Reading file and saving linest to a vector*/
		SourceFileManager* fileManager = new SourceFileManager("../IntegrationTesting/Source1.txt");
		vector<string> fileLines = fileManager->readFile();

		/*Parsing fileLines to a LexerTokens*/
		vector<LexerToken*> tokensList = Lexer::parse(fileLines);

		SourceParser* sourceParser = new SourceParser(tokensList);
		Node* rootNode = sourceParser->parse();
	}
};