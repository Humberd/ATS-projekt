#include "Parent.h"
#include <set>

Parent::Parent(map<int, vector<int>>& intTable, map<int, vector<Node*>>& stmtTable) {
	this->statementTable = stmtTable;
	this->parentMap = intTable;
}


vector<STMT*> Parent::getParent(STMT* s, bool goDeep) {
	vector<STMT*> output;
	if (goDeep == false) {
		output = getParentWithoutDeep(s);
	} else {
		output = getParentWithDeep(s);
	}
	return output;
}

vector<STMT*> Parent::getParentOf(STMT* s, bool goDeep) {
	vector<STMT*> output;
	if (goDeep == false) {
		output = getParentOfWithoutDeep(s);
	} else {
		output = getParentOfWithDeep(s);
	}
	return output;
}

bool Parent::isParent(STMT* s1, STMT* s2, bool goDeep) {
	bool output = false;
	if (goDeep == false) {
		output = isParentWithoutDeep(s1, s2);
	} else {
		output = isParentWithDeep(s1, s2);
	}
	return output;
}

vector<STMT*> Parent::getParentWithoutDeep(STMT* s) {
	vector<STMT*> result;

	vector<int> children;
	try {
		children = parentMap.at(s->getSTMT());
	} catch (out_of_range&) {
		return result;
	}

	for (auto child : children) {
		result.push_back(new STMT(child));
	}

	delete s;

	return result;

}


vector<STMT*> Parent::getParentWithDeep(STMT* s) {
	vector<STMT*> result;

	getParentWithDeepSingle(s->getSTMT(), result);

	delete s;

	return result;
}


void Parent::getParentWithDeepSingle(int childLine, vector<STMT*>& response) {
	vector<int> children;
	try {
		children = parentMap.at(childLine);
	} catch (out_of_range&) {
		return;
	}

	for (auto child : children) {
		response.push_back(new STMT(child));
		getParentWithDeepSingle(child, response);
	}
}

vector<STMT*> Parent::getParentOfWithoutDeep(STMT* s) {
	vector<STMT*> result;

	for (auto entrySet : parentMap) {
		for (auto child : entrySet.second) {
			if (child == s->getSTMT()) {
				result.push_back(new STMT(entrySet.first));
				return result;
			}
		}
	}

	delete s;
	return result;
}

vector<STMT*> Parent::getParentOfWithDeep(STMT* s) {
	vector<STMT*> result;

	getParentOfWithDeepSingle(s->getSTMT(), result);

	delete s;

	return result;
}

void Parent::getParentOfWithDeepSingle(int childLine, vector<STMT*>& response) {
	for (auto entrySet : parentMap) {
		for (auto child : entrySet.second) {
			if (child == childLine) {
				response.push_back(new STMT(entrySet.first));
				getParentOfWithDeepSingle(entrySet.first, response);
				return;
			}
		}
	}

}


bool Parent::isParentWithoutDeep(STMT* s1, STMT* s2) {
	vector<int> children;
	try {
		children = parentMap.at(s1->getSTMT());
	} catch (out_of_range&) {
		return false;
	}

	bool result = any_of(children.begin(), children.end(),
	                     [s2](int child) {
		                     return child == s2->getSTMT();
	                     });

	delete s1 , s2;

	return result;
}

bool Parent::isParentWithDeep(STMT* s1, STMT* s2) {
	bool result = false;

	isParentWithDeepSingle(s1->getSTMT(), s2->getSTMT(), result);

	return result;
}

void Parent::isParentWithDeepSingle(int parentLine, int childLine, bool& result) {
	vector<int> children;
	try {
		children = parentMap.at(parentLine);
	} catch (out_of_range&) {
		result |= false;
		return;
	}

	for (auto childNumber : children) {
		if (childNumber == childLine) {
			result = true;
			return;
		}

		if (result == true) {
			return;
		}

		isParentWithDeepSingle(childNumber, childLine, result);
	}
}
