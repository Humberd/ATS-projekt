#include <vector>
#include "STMT.h"
#include "SpaDataContainer.h"

using namespace std;

class Next {

public:
	explicit Next(SpaDataContainer* spaDataContainer);
	vector<STMT*> goNext(STMT* s, bool goDeep);
	vector<STMT*> goBefore(STMT* s, bool goDeep);
	bool isNext(STMT* s1, STMT* s2, bool goDeep);
private:
	SpaDataContainer* spaDataContainer;
	vector<STMT*> goNextWithoutDeep(STMT* s);
	vector<STMT*> goNextWithDeep(STMT* s);
	void goNextWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);
	vector<STMT*> goBeforeWithoutDeep(STMT* s);
	vector<STMT*> goBeforeWithDeep(STMT* s);
	void goBeforeWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);
	bool isNextWithoutDeep(STMT* s1, STMT* s2);
	bool isNextWithDeep(STMT* s1, STMT* s2);
	void isNextWithDeepSingle(NodeFlowWrapper* currentNode, bool& found, int& wantedProgramLine, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);

};
