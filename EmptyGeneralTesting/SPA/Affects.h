#include <vector>
#include "ASSIGN.h"
#include "SpaDataContainer.h"
#include "STMT.h"
#include "PkbBridge.h"
using namespace std;

class Affects {
public:
	explicit Affects(SpaDataContainer* spaDataContainer, PkbBrigde* pkbBridge);
	vector<ASSIGN*> getAffects(ASSIGN* a, bool goDeep);
	vector<ASSIGN*> getAffectsBy(ASSIGN* a, bool goDeep);
	bool ifAffects(ASSIGN* a1, ASSIGN* a2, bool goDeep);
private:
	SpaDataContainer* spaDataContainer;
	PkbBrigde* pkbBridge;

	vector<ASSIGN*> getAffectsWithoutDeep(ASSIGN* a);
	vector<ASSIGN*> getAffectsWithDeep(ASSIGN* a);
	void getAffectsWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);
	vector<ASSIGN*> getAffectsByWithoutDeep(ASSIGN* a);
	vector<ASSIGN*> getAffectsByWithDeep(ASSIGN* a);
	void getAffectsByWithDeepSingle(NodeFlowWrapper* currentNode, vector<STMT*>& response, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);
	bool ifAffectsWithoutDeep(ASSIGN* a1, ASSIGN* a2);
	bool ifAffectsWithDeep(ASSIGN* a1, ASSIGN* a2);
	void ifAffectsWithDeepSingle(NodeFlowWrapper* currentNode, bool& found, int& wantedProgramLine, vector<NodeFlowWrapper*>& alreadyBeenToSpecialNodes, bool& firstNode);
};
