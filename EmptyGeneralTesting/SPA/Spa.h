#pragma once
#include "Node.h"
#include "SpaDataContainer.h"

using namespace std;

class Spa {

private:
	Spa();
	~Spa();

public:
	static Node* generateAstFromFile(string filePath);
	static SpaDataContainer* generateHelperTables(Node* rootNode);
};
