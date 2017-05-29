#include "Parent.h"
#include <set>
Parent* Parent::instance = 0;

Parent::Parent(map<int, vector<int>> intTable, map<int, vector<Node*>> stmtTable) {
	this->statementTable = stmtTable;
	this->parentMap = intTable;
	/*
	vector<int> test;
	test.push_back(5);
	test.push_back(4);
	test.push_back(3);

	vector<int> test2;
	test2.push_back(10);
	test2.push_back(20);
	test2.push_back(30);

	vector<int> test3;
	test3.push_back(66);
	test3.push_back(65);
	test3.push_back(66);

	parentMap[1] = test;
	parentMap[2] = test2;
	parentMap[4] = test3;
	*/
	SourceFileManager* fileManager = new SourceFileManager("../IntegrationTesting/Source2.txt");
	vector<string> fileLines = fileManager->readFile();

	/*Parsing fileLines to a LexerTokens*/
	vector<LexerToken*> tokensList = Lexer::parse(fileLines);

	/*Starting the actual parser*/
	SourceParser* sourceParser = new SourceParser(tokensList);
	ProgramLineEvaluator* evaluator = new ProgramLineEvaluator;
	try {
		Node* rootNode = sourceParser->parse();
		rootNode->validate();
		evaluator->evaluate(rootNode);
		mainNode = rootNode;
	} catch (exception& e) {
	}

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

Parent* Parent::getInstance(map<int, vector<int>> intTable, map<int, vector<Node*>> stmtTable) {
	if (!instance) {
		instance = new Parent(intTable, stmtTable);
	}

	return instance;
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
