#pragma once
#include <vector>
#include "InjectRequest.h"

using namespace std;

class InjectRequestsContainer {
public:
	string procedureName;
	vector<InjectRequest*> injectRequests;

	explicit InjectRequestsContainer();
	~InjectRequestsContainer();
};
