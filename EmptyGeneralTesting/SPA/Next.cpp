#include "Next.h"

Next::Next(map<int, vector<Node*>> statementTable)
{
	this->statementTable = statementTable;
}

vector<STMT*> Next::goNext(STMT * s, bool goDeep)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goPrevious(STMT * s, bool goDeep)
{
	return vector<STMT*>();
}

bool Next::isNext(STMT * s1, STMT * s2, bool goDeep)
{
	return goDeep ? isNextDeep(s1, s2) : isNext(s1, s2);
}

Next * Next::getInstance(map<int, vector<Node*>> statementTable)
{
	if (!instance) {
		instance = new Next(statementTable);
	}

	return instance;
}

vector<STMT*> Next::goNextWithoutDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextWithDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithDeep(STMT * s)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithoutDeep(STMT * s)
{
	return vector<STMT*>();
}

bool Next::isNextDeep(STMT * s1, STMT * s2)
{
	return false;
}

bool Next::isNext(STMT * s1, STMT * s2)
{
	return false;
}
