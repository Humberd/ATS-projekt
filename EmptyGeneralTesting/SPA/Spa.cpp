#include "Spa.h"
#include "SourceFileManager.h"
#include "Lexer.h"
#include "SourceParser.h"
#include "ProgramLineEvaluator.h"
#include "TreeAnalyzer.h"
#include "QLexer.h"
#include "QuerySourceParser.h"
#include "DeclaredVariable.h"
#include "DeclarationsSourceParser.h"
#include "QueryEvaluator.h"
#include "PkbBridgeMockImpl.h"
#include "ResponseParser.h"
#include "PkbBridgeImpl.h"

Spa::Spa() {
}

Spa::~Spa() {
}

Node* Spa::generateAstFromFile(string filePath) {
	/*Reading file and saving lines to a vector*/
	SourceFileManager* fileManager = new SourceFileManager(filePath);
	vector<string> fileLines = fileManager->readFile();

	/*Generate LexerTokens from fileLines*/
	vector<LexerToken*> tokensList = Lexer::parse(fileLines);

	/*---Starting the parsing process---*/
	SourceParser* sourceParser = new SourceParser(tokensList);
	ProgramLineEvaluator* programLineEvaluator = new ProgramLineEvaluator;

	/*Here I tell the parser to parse tokensList and return me a rootNode*/
	Node* rootNode = sourceParser->parse();
	/*Need to check if the AST is valid.
	 * By valid I mean:
	 * - nodes have required number of children, for example: assignNode has stated 2 children
	 * - AST graph is not looping, for example: a parent node is not a children of its own child
	 */
	rootNode->validate();
	/*Need traverse through all the tree to generate a programLineNumber for each of the node
	 * You can read more about it in "ProgramLineEvaluator.h" file
	 */
	programLineEvaluator->evaluate(rootNode);

	/*Here I clean redundant objects*/
	delete fileManager;
	for (auto token : tokensList) {
		delete token;
	}
	tokensList.clear();
	delete sourceParser;
	delete programLineEvaluator;


	return rootNode;
}

SpaDataContainer* Spa::generateHelperTables(Node* rootNode) {
	return TreeAnalyzer::analyzeTree(rootNode);
}


list<string> Spa::evaluateExpression(string declarationVariables, string query, SpaDataContainer* spaDataContainer) {
	vector<QLexerToken*> queryDeclarationsTokens = QLexer::parseDeclarations(declarationVariables);
	vector<QLexerToken*> queryTokens = QLexer::parseQuery(query);

	DeclarationsSourceParser declarationsSourceParser(queryDeclarationsTokens);

	vector<DeclaredVariable*> declaredVariables = declarationsSourceParser.parse();
	QueryRequest* queryRequest = QuerySourceParser::cleanParse(queryTokens);

	PkbBrigde* pkbBrigde = new PkbBridgeImpl(spaDataContainer);
	QueryEvaluator* queryEvaluator = new QueryEvaluator(declaredVariables, queryRequest, spaDataContainer);
	queryEvaluator->setPkbBrigde(pkbBrigde);
	queryEvaluator->evaluate();
	vector<vector<string>> response =queryEvaluator->evaluateReturn();

	list<string> parsedResponse = ResponseParser::parse(response);


	for (auto token : queryDeclarationsTokens) {
		delete token;
	}
	for (auto token : queryTokens) {
		delete token;
	}
	for (auto var : declaredVariables) {
		delete var;
	}
	delete queryRequest , pkbBrigde , queryEvaluator;

	return parsedResponse;
}
