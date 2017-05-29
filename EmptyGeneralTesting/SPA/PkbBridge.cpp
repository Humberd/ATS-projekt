#include "PkbBridge.h"


PkbBrigde::PkbBrigde() {
}

PkbBrigde::~PkbBrigde() {
}

STMT* PkbBrigde::parseStringToStmt(string statement) const {
	return new STMT(stoi(statement));
}


VAR* PkbBrigde::parseStringToVar(string variable) const {
	return new VAR(variable);
}

PROC* PkbBrigde::parceStringToProc(string procedure) const {
	return new PROC(procedure);
}

vector<string> PkbBrigde::parseStmtsToStrings(vector<STMT*>& statements) const {
	vector<string> parsedResponse;

	for (auto stat : statements) {
		parsedResponse.push_back(to_string(stat->getSTMT()));
		delete stat;
	}

	return parsedResponse;
}

vector<string> PkbBrigde::parseProceduresToStrings(vector<PROC*>& procedures) const {
	vector<string> parsedResponse;

	for (auto proc : procedures) {
		parsedResponse.push_back(proc->getProc());
		delete proc;
	}

	return parsedResponse;
}

vector<string> PkbBrigde::parseVariablesToStrings(vector<VAR*>& variables) const {
	vector<string> parsedResponse;

	for (auto var : variables) {
		parsedResponse.push_back(var->getVAR());
		delete var;
	}

	return parsedResponse;
}
