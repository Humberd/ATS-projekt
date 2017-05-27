#include "Follows.h"
Follows *Follows::instance = 0;




Follows * Follows::getInstance(map<int, vector<int>> _map)
{
	if (!instance) {
		instance = new Follows(_map);
	}

	return instance;
}


Follows::Follows(map<int, vector<int>> _map)
{
	this->followsTable = _map;
}

Follows::~Follows()
{
}

void Follows::setFollows(STMT * s1, STMT * s2)
{
}

vector<STMT*> Follows::getFollows(STMT * s, bool goDeep)
{
	if (goDeep)
	{
		return getFollowsWithDeep(s);
	}
	else
	{
		return getFollowsWithoutDeep(s);
	}
}

vector<STMT*> Follows::getFollowsBy(STMT * s, bool goDeep)
{
	if (goDeep)
	{
		return getFollowsByWithDeep(s);
	}
	else
	{
		return getFollowsByWithoutDeep(s);
	}
}

bool Follows::isFollows(STMT * s1, STMT * s2, bool goDeep)
{
	if (goDeep)
	{
		return isFollowsWithDeep(s1,s2);
	}
	else
	{
		return isFollowsWithoutDeep(s1, s2);
	}
}

bool Follows::isFollowsBy(STMT * s1, STMT * s2, bool goDeep)
{
	if (goDeep)
	{
		return isFollowsByWithDeep(s1, s2);
	}
	else
	{
		return isFollowsByWithoutDeep(s1, s2);
	}
}
//////////////

vector<STMT*> Follows::getFollowsWithoutDeep(STMT * a)
{
	vector<STMT*> result;

	for (map<int, vector<int>>::iterator it = followsTable.begin(); it != followsTable.end(); ++it)
	{
		if (followsTable[it->first].size() > 0 && followsTable[it->first].at(0) == a->getSTMT())
		{
			result.push_back(new STMT(it->first));
		}
	}
	return result;
}

vector<STMT*> Follows::getFollowsWithDeep(STMT * a)
{
	vector<STMT*> result;
	bool goLoop = true;
	int which = a->getSTMT();
	while (goLoop)
	{
		goLoop = false;
		for (map<int, vector<int>>::iterator it = followsTable.begin(); it != followsTable.end(); ++it)
		{
			if (followsTable[it->first].size() > 0 && followsTable[it->first].at(0) == which)
			{
				result.push_back(new STMT(it->first));
				which = it->first;
				goLoop = true;
				break;
			}
		}
	}
	return result;
}

vector<STMT*> Follows::getFollowsByWithDeep(STMT * a)
{
	vector<STMT*> result;
	int which = a->getSTMT();
	while (true)
	{	

		if (followsTable[which].size() > 0)
		{
			result.push_back(new STMT(followsTable[which][0]));
			which = followsTable[which][0];
		}
		else
		{
			break;
		}
		
	}

	return result;
}

vector<STMT*> Follows::getFollowsByWithoutDeep(STMT * a)
{
	vector<STMT*> result;
	for (int i = 0; i < followsTable[a->getSTMT()].size();i++)
	{
		result.push_back(new STMT(followsTable[a->getSTMT()][i]));
	}
	return result;
}

bool Follows::isFollowsWithoutDeep(STMT * a1, STMT * a2)
{

	if (followsTable.find(a1->getSTMT()) == followsTable.end())
	{
		return false;
	}
	else {
		if (followsTable[a1->getSTMT()].size() > 0)
		{
			if (followsTable[a1->getSTMT()].at(0) == a2->getSTMT())
			{
				return true;
			}
		}
	}

	return false;
}

bool Follows::isFollowsWithDeep(STMT * a1, STMT * a2)
{
	int which = a1->getSTMT();
	while (true)
	{
		if (followsTable.find(which) == followsTable.end())
		{
			return false;
		}
		else {
			if (followsTable[which].size() > 0)
			{
				if (followsTable[which].at(0) == a2->getSTMT())
				{
					return true;
				}
				else
				{
					which = followsTable[which].at(0);
					continue;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool Follows::isFollowsByWithoutDeep(STMT * a1, STMT * a2)
{
	if (followsTable.find(a2->getSTMT()) == followsTable.end())
	{
		return false;
	}
	else {
		if (followsTable[a2->getSTMT()].size() > 0)
		{
			if (followsTable[a2->getSTMT()].at(0) == a1->getSTMT())
			{
				return true;
			}
		}
	}

	return false;
}

bool Follows::isFollowsByWithDeep(STMT * a1, STMT * a2) //blad
{
	vector<int> help;
	int which = a2->getSTMT();
	while (true)
	{

		if (followsTable[which].size() > 0)
		{
			help.push_back(followsTable[which][0]);
			which = followsTable[which][0];
		}
		else
		{
			break;
		}
	}

	if ((find(help.begin(), help.end(), a1->getSTMT()) != help.end()))
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
