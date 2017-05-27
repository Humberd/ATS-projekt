#pragma once
#include "Node.h"
#include "SpaDataContainer.h"
#include <list>

using namespace std;

class Spa {

private:
	Spa();
	~Spa();

public:
	static Node* generateAstFromFile(string filePath);
	static SpaDataContainer* generateHelperTables(Node* rootNode);
	static list<string> evaluateExpression(string declarationVariables, string query, SpaDataContainer* spaDataContainer);
};
