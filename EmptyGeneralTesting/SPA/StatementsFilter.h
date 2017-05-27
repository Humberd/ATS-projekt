#pragma once
#include <vector>
#include "SpaDataContainer.h"
#include <set>

using namespace std;

class StatementsFilter {
public:
	explicit StatementsFilter();
	~StatementsFilter();

	static vector<string> filter(vector<string>& statements, string type, SpaDataContainer* spaDataContainer);

	static vector<string> getNodesWithType(string type, SpaDataContainer* spaDataContainer);
	static vector<string> getPropertyValues(string type, string propertyName, SpaDataContainer* spaDataContainer, vector<string>& resulsts);
	static vector<string> getCallPropertyValues(SpaDataContainer* spaDataContainer, vector<string>& resulsts);

	static vector<string> getAllVariables(SpaDataContainer* spaDataContainer);
	static vector<string> getAllConstants(SpaDataContainer* spaDataContainer);
	static void getAllConstantsTreeTraverser(Node* node, set<string>& globalConstants);
	static vector<string> getAllProcedures(SpaDataContainer* spaDataContainer);

};
