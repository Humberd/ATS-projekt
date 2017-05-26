#include "Next.h"

Next::Next(map<int, vector<int>> _affectsMap)
{
}

vector<STMT*> Next::goNext(STMT * a, bool goDeep)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goPrevious(STMT * a, bool goDeep)
{
	return vector<STMT*>();
}

bool Next::isNext(Next * a1, STMT * a2, bool goDeep)
{
	return false;
}

Next * Next::getInstance(map<int, vector<int>> _affectsMap)
{
	return nullptr;
}

vector<STMT*> Next::goNextWithoutDeep(STMT * a)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextWithDeep(STMT * a)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithDeep(STMT * a)
{
	return vector<STMT*>();
}

vector<STMT*> Next::goNextByWithoutDeep(STMT * a)
{
	return vector<STMT*>();
}

bool Next::isNextWithoutDeep(STMT * a1, STMT * a2)
{
	return false;
}

bool Next::isNextWithDeep(STMT * a1, STMT * a2)
{
	return false;
}
