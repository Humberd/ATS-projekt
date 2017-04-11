#include "Modifies.h"

Modifies *Modifies::instance = 0;

Modifies * Modifies::getInstance()
{
	if (!instance) {
		instance = new Modifies();
	}

	return instance;
}

Modifies::Modifies()
{
}

Modifies::~Modifies()
{
}

void Modifies::setModifies(STMT s, VAR v)
{
	modifiesSTMT[s].push_back(v);
}

void Modifies::setModifies(PROC p, VAR v)
{
	modifiesPROC[p].push_back(v);
}

vector<STMT> Modifies::getModifiesSTMT(VAR v)
{
	vector<STMT> returnModifiesList;

	for (map<STMT, vector<VAR>>::iterator it = modifiesSTMT.begin(); it != modifiesSTMT.end(); ++it) {
		if (isModifies(it->first, v)) {
			returnModifiesList.push_back(it->first);
		}
	}

	return returnModifiesList;
}

vector<PROC> Modifies::getModifiesPROC(VAR v)
{
	vector<PROC> returnModifiesList;

	for (map<PROC, vector<VAR>>::iterator it = modifiesPROC.begin(); it != modifiesPROC.end(); ++it) {
		if (isModifies(it->first, v)) {
			returnModifiesList.push_back(it->first);
		}
	}

	return returnModifiesList;
}

vector<VAR> Modifies::getModifiesBy(STMT s)
{
	if (modifiesSTMT.count(s) != 0) {
		return modifiesSTMT[s];
	}

	return vector<VAR>();
}

vector<VAR> Modifies::getModifiesBy(PROC p)
{
	if (modifiesPROC.count(p) != 0) {
		return modifiesPROC[p];
	}

	return vector<VAR>();
}

bool Modifies::isModifies(STMT s, VAR v)
{
	if (modifiesSTMT.count(s) == 0)
	{
		return false;
	}
	else
	{
		for (VAR proc : modifiesSTMT[s]) {
			if (proc == v) {
				return true;
			}
		}

		return false;
	}
}

bool Modifies::isModifies(PROC p, VAR v)
{
	if (modifiesPROC.count(p) == 0)
	{
		return false;
	}
	else
	{
		for (VAR proc : modifiesPROC[p]) {
			if (proc == v) {
				return true;
			}
		}

		return false;
	}
}
