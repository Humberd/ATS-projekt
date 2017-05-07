#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SPA/SourceFileManager.h"
#include "../SPA/Lexer.h"
#include "../SPA/SourceParser.h"
#include "../SPA/ProgramLineEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SourceToASTTest) {
	TEST_METHOD(SourceToAST_AssignmentSource) {
		/*Reading file and saving linest to a vector*/
		SourceFileManager* fileManager = new SourceFileManager("../IntegrationTesting/Source1.txt");
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
			rootNode->prettyPrint();
		} catch (exception& e) {
			Logger::WriteMessage(e.what());
		}
	}
};