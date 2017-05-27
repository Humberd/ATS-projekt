#pragma once
#include <vector>
#include "SpaDataContainer.h"

using namespace std;

class StatementsFilter {
public:
	explicit StatementsFilter();
	~StatementsFilter();

	static vector<string> filter(vector<string>& statements, string type, SpaDataContainer* spaDataContainer);
};
