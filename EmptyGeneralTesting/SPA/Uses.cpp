#include "Uses.h"

Uses *Uses::instance = 0;

Uses * Uses::getInstance()
{
	if (!instance) {
		instance = new Uses();
	}

	return instance;
}

Uses::Uses()
{
}

Uses::~Uses()
{
}

void Uses::setUses(ASSIGN* a, VAR* v)
{
	usesASSIGN[a->getASSIGN()].push_back(v);
}

void Uses::setUses(STMT* s, VAR* v)
{
	usesSTMT[s->getSTMT()].push_back(v);
}

void Uses::setUses(PROC* p, VAR* v)
{
	usesPROC[p->getProc()].push_back(v);
}

vector<VAR*> Uses::getUses(ASSIGN* a)
{
	if (usesASSIGN.count(a->getASSIGN()) != 0) {
		return usesASSIGN[a->getASSIGN()];
	}

	return vector<VAR*>();
}

vector<VAR*> Uses::getUses(STMT* s)
{
	if (usesSTMT.count(s->getSTMT()) != 0) {
		return usesSTMT[s->getSTMT()];
	}

	return vector<VAR*>();
}

vector<VAR*> Uses::getUses(PROC* p)
{
	if (usesPROC.count(p->getProc()) != 0) {
		return usesPROC[p->getProc()];
	}

	return vector<VAR*>();
}

vector<ASSIGN*> Uses::getUsedByASSIGN(VAR* v)
{
	vector<ASSIGN*> returnModifiesList;

	for (map<int, vector<VAR*>>::iterator it = usesASSIGN.begin(); it != usesASSIGN.end(); ++it) {
		if (isUsed(new ASSIGN(it->first), v)) {
			returnModifiesList.push_back(new ASSIGN(it->first));
		}
	}

	return returnModifiesList;
}

vector<STMT*> Uses::getUsesBySTMT(VAR* v)
{
	vector<STMT*> returnModifiesList;

	for (map<int, vector<VAR*>>::iterator it = usesSTMT.begin(); it != usesSTMT.end(); ++it) {
		if (isUsed(new STMT(it->first), v)) {
			returnModifiesList.push_back(new STMT(it->first));
		}
	}

	return returnModifiesList;
}

vector<PROC*> Uses::getUsesByPROC(VAR* v)
{
	vector<PROC*> returnModifiesList;

	for (map<string, vector<VAR*>>::iterator it = usesPROC.begin(); it != usesPROC.end(); ++it) {
		if (isUsed(new PROC(it->first), v)) {
			returnModifiesList.push_back(new PROC(it->first));
		}
	}

	return returnModifiesList;
}

bool Uses::isUsed(ASSIGN* a, VAR* v)
{
	if (usesASSIGN.count(a->getASSIGN()) == 0)
	{
		return false;
	}
	else
	{
		for (VAR* var : usesASSIGN[a->getASSIGN()]) {
			if (var->getVAR() == v->getVAR()) {
				return true;
			}
		}

		return false;
	}
}

bool Uses::isUsed(STMT* s, VAR* v)
{
	if (usesSTMT.count(s->getSTMT()) == 0)
	{
		return false;
	}
	else
	{
		for (VAR* proc : usesSTMT[s->getSTMT()]) {
			if (proc->getVAR() == v->getVAR()) {
				return true;
			}
		}

		return false;
	}
}

bool Uses::isUsed(PROC* p, VAR* v)
{
	if (usesPROC.count(p->getProc()) == 0)
	{
		return false;
	}
	else
	{
		for (VAR* var : usesPROC[p->getProc()]) {
			if (var->getVAR() == v->getVAR()) {
				return true;
			}
		}

		return false;
	}
}
	