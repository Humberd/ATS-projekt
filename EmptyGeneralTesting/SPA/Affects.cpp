#include "Affects.h"

Affects::Affects(map<int, vector<int>> _affectsMap)
{
	this->affectsMap = _affectsMap;
}

vector<ASSIGN*> Affects::getAffects(ASSIGN * a, bool goDeep)
{
	return vector<ASSIGN*>();
}

vector<ASSIGN*> Affects::getAffectsBy(ASSIGN * a, bool goDeep)
{
	return vector<ASSIGN*>();
}

bool Affects::ifAffects(ASSIGN * a1, ASSIGN * a2, bool goDeep)
{
	return false;
}

Affects * Affects::getInstance(map<int, vector<int>> _affectsMap)
{
	if (!instance) {
		instance = new Affects(_affectsMap);
	}
	return instance;
}

vector<ASSIGN*> Affects::getAffectsWithoutDeep(ASSIGN * a)
{
	vector<ASSIGN*> result;
	if (!(affectsMap.find(a->getASSIGN()) == affectsMap.end()))
	{
		for (int i = 0; i < affectsMap[a->getASSIGN()].size(); i++)
		{
			ASSIGN* as = new ASSIGN(affectsMap[a->getASSIGN()].at(i));
			result.push_back(as);
		}
	}
	return result;
}

vector<ASSIGN*> Affects::getAffectsWithDeep(ASSIGN * a)
{

	vector<ASSIGN*> result;


	return vector<ASSIGN*>();
}

vector<ASSIGN*> Affects::getAffectsByWithDeep(ASSIGN * a)
{
	return vector<ASSIGN*>();
}

vector<ASSIGN*> Affects::getAffectsByWithoutDeep(ASSIGN * a)
{
	return vector<ASSIGN*>();
}

bool Affects::ifAffectsWithoutDeep(ASSIGN * a1, ASSIGN * a2)
{
	return false;
}

bool Affects::ifAffectsWithDeep(ASSIGN * a1, ASSIGN * a2)
{
	return false;
}

