#include "Modifies.h"

Modifies *Modifies::instance = 0;

Modifies * Modifies::getInstance(map<int, vector<string>> modifiesStatementTable, map<string, vector<string>> modifiesProcedureTable)
{
	if (!instance) {
		instance = new Modifies(modifiesStatementTable, modifiesProcedureTable);
	}

	return instance;
}

Modifies::Modifies(map<int, vector<string>> modifiesStatementTable, map<string, vector<string>> modifiesProcedureTable)
{

	for (map<string, vector<string>>::const_iterator it = modifiesProcedureTable.begin(); it != modifiesProcedureTable.end(); ++it) {
		vector<VAR*> tmp;

		for (string value : modifiesProcedureTable.at(it->first)) {
			tmp.push_back(new VAR(value));
		}

		this->modifiesPROC.insert(pair<string, vector<VAR*>>(it->first, tmp));
	}

	for (map<int, vector<string>>::const_iterator it = modifiesStatementTable.begin(); it != modifiesStatementTable.end(); ++it) {
		vector<VAR*> tmp;

		for (string value : modifiesStatementTable.at(it->first)) {
			tmp.push_back(new VAR(value));
		}

		this->modifiesSTMT.insert(pair<int, vector<VAR*>>(it->first, tmp));
	}
}

Modifies::~Modifies()
{
}

void Modifies::setModifies(STMT* s, VAR* v)
{
//	modifiesSTMT[s].push_back(v);
	if (modifiesSTMT.count(s->getSTMT()) == 0)
	{
		vector<VAR*> tmp;
		tmp.push_back(v);
		modifiesSTMT.insert(pair<int, vector<VAR*>>(s->getSTMT(), tmp));
	}
	else
	{
		modifiesSTMT.at(s->getSTMT()).push_back(v);
	}
}

void Modifies::setModifies(PROC* p, VAR* v)
{
//	modifiesPROC[p].push_back(v);
	if (modifiesPROC.count(p->getProc()) == 0)
	{
		vector<VAR*> tmp;
		tmp.push_back(v);
		modifiesPROC.insert(pair<string, vector<VAR*>>(p->getProc(), tmp));
	}
	else
	{
		modifiesPROC.at(p->getProc()).push_back(v);
	}
}

vector<STMT*> Modifies::getModifiesSTMT(VAR* v)
{
	vector<STMT*> returnModifiesList;

	for (map<int, vector<VAR*>>::iterator it = modifiesSTMT.begin(); it != modifiesSTMT.end(); ++it) {
		if (isModifies(it->first, v)) {
			returnModifiesList.push_back(new STMT(it->first));
		}
	}

	return returnModifiesList;
}

vector<PROC*> Modifies::getModifiesPROC(VAR* v)
{
	vector<PROC*> returnModifiesList;

	for (map<string, vector<VAR*>>::iterator it = modifiesPROC.begin(); it != modifiesPROC.end(); ++it) {
		if (isModifies(it->first, v)) {
			returnModifiesList.push_back(new PROC(it->first));
		}
	}

	return returnModifiesList;
}

vector<VAR*> Modifies::getModifiesBy(STMT* s)
{
	if (modifiesSTMT.count(s->getSTMT()) != 0) {
		return modifiesSTMT.at(s->getSTMT());
	}

	return vector<VAR*>();
}

vector<VAR*> Modifies::getModifiesBy(PROC* p)
{
	if (modifiesPROC.count(p->getProc()) != 0) {
		return modifiesPROC.at(p->getProc());
	}

	return vector<VAR*>();
}

bool Modifies::isModifies(int s, VAR* v)
{
	if (modifiesSTMT.count(s) == 0)
	{
		return false;
	}
	else
	{
		for (VAR* var : modifiesSTMT.at(s)) {
			if (var->getVAR() == v->getVAR()) {
				return true;
			}
		}

		return false;
	}
}

bool Modifies::isModifies(string p, VAR* v)
{
	if (modifiesPROC.count(p) == 0)
	{
		return false;
	}
	else
	{
		for (VAR* var : modifiesPROC.at(p)) {
			if (var->getVAR() == v->getVAR()) {
				return true;
			}
		}

		return false;
	}
}
