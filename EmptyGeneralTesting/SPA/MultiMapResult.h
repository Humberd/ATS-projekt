#pragma once
#include <vector>
#include <map>
#include "InjectRequest.h"

using namespace std;

class MultiMapResult {
public:
	map<int, vector<string>> statementMap;
	map<string, vector<string>> procedureMap;
	vector<vector<InjectRequest*>> injectRequestsCollection;

	explicit MultiMapResult();
	~MultiMapResult();
};
