#include "PkbBridge.h"


PkbBrigde::PkbBrigde() {
}

PkbBrigde::~PkbBrigde() {
}

STMT* PkbBrigde::parseStringToStmt(string statement) const {
	return new STMT(stoi(statement));
}

vector<string> PkbBrigde::parseStmtsToStrings(vector<STMT*>& statements) const {
	vector<string> parsedResponse;

	for (auto stat : statements) {
		parsedResponse.push_back(to_string(stat->getSTMT()));
		delete stat;
	}

	return parsedResponse;
}
