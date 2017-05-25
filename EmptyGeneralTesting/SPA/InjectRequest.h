#pragma once
#include <vector>

using namespace std;

class InjectRequest {
public:
	string callProcedure;
	vector<int> injectToStatements;
	string injectToProcedure;

	explicit InjectRequest();
	~InjectRequest();
};