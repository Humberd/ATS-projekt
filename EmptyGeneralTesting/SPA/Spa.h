#pragma once
#include "Node.h"

using namespace std;

class Spa {

private:
	Spa();
	~Spa();

public:
	static Node* generateAstFromFile(string filePath);
};
