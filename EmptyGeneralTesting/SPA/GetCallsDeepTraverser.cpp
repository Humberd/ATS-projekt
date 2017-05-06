#include "GetCallsDeepTraverser.h"

GetCallsDeepTraverser::GetCallsDeepTraverser(map<string, vector<PROC*>> callsTable) : callsTable(callsTable) {
}

/*Ta metoda poci¹ga te procedury z mapy ktore pasuj¹ dla get calls deep
 * Dla GetCallsFromDeep zmien implementacje metody, jak bedziesz copy paste robil, a reszta powinna byc ok
 * 
 * Ponadto nie sprawdzaj, czy cos istnieje w mapie za pomoca: callsTable[p], bo w tym wypadku jesli nie bedzie, to automatycznie to stworzy
 * Wiêcej info masz tutaj http://stackoverflow.com/a/33239463/4256929
 */
vector<PROC*> GetCallsDeepTraverser::getProceduresFromCallsTable(PROC* p) {
	if (callsTable.count(p->getProc()) == 1) {
		return callsTable.at(p->getProc());
	} else {
		return vector<PROC*>();
	}
}

bool GetCallsDeepTraverser::isGatheringListFull() {
	return this->gatheringList.size() == this->callsTable.size();
}

void GetCallsDeepTraverser::addChildToGatheringList(PROC* p) {
	this->gatheringList.insert(p->getProc());
}


vector<PROC*> GetCallsDeepTraverser::filterAlreadyVisitedProcedures(vector<PROC*> children) {
	vector<PROC*> filteredChildren;
	/*If the child is in a gatheringList, then I throw it out to the trash, because there is no need to traverse it again*/
	/*If the child isn't in the gatheringList, then I return it*/
	for (auto child : children) {
		if (gatheringList.count(child->getProc()) == 0) {
			filteredChildren.push_back(child);
		}
	}
	return filteredChildren;
}

void GetCallsDeepTraverser::traverse(PROC* parentProcedure) {
	/*First I need to get all the procedures that are invoked from parent procedure*/
	vector<PROC*> childrenProcedures = this->getProceduresFromCallsTable(parentProcedure);

	/*I need to filter out already visited procedures, because I don't need to traverse it again */
	vector<PROC*> filteredProcedures = this->filterAlreadyVisitedProcedures(childrenProcedures);

	/*If it happens that I filtered all the children procedures, then I end*/
	if (filteredProcedures.size() == 0) {
		return;
	}

	/*Now I add all the filtered children to the gatheringTable*/
	for (auto child : filteredProcedures) {
		this->addChildToGatheringList(child);
	}

	/*If it happens, that the gatheringTable becomes full, then I return*/
	if (isGatheringListFull()) {
		return;
	} else {
		/*Now I need to traverse on every filtered child*/
		for (auto child : filteredProcedures) {

			this->traverse(child);

			/*When backing from traversin a child I need to check if list is full,
			 * so that I wouldn't have to traverse the rest of the sibling in this for loop
			 */
			if (isGatheringListFull()) {
				return;
			}
		}
	}
}

set<PROC*> GetCallsDeepTraverser::getGatheringList() {
	set<PROC*> returnList;

	for (string procName : this->gatheringList) {
		returnList.insert(new PROC(procName));
	}

	return returnList;
}
