#pragma once
#include "Node.h"

using namespace std;

class Spa {

private:
	Spa();

public:
	~Spa();

	static Node* generateAstFromFile(string filePath);
};
