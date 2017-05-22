#include "UsesTag.h"
//#include "../SPA/Uses.h"
#include "../SPA/Next.h"
//ZMIENICCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
UsesTag::UsesTag(QueryParts queryParts, int which)
{
	_queryParts = queryParts;
	_which = which;
}


UsesTag::~UsesTag()
{
}

list<string> UsesTag::DoQuery()
{
	//Uses uses;
	list<string> finalResult;
	string type;
	string selectItem = _queryParts.selectingItem;
	transform(selectItem.begin(), selectItem.end(), selectItem.begin(), tolower);
	bool InDepth = false;
	if (_queryParts.parts[_which].tag[_queryParts.parts[_which].tag.size() - 1] == '*')
	{
		InDepth = true;
	}
	if (_queryParts.parts[_which].parameteresInBracket.size() != 2)
	{
		return finalResult;
	}
	if (selectItem == "boolean")
	{

	}
	else
	{
		int whichParam = 0;
		if (_queryParts.selectingItem == _queryParts.parts[_which].parameteresInBracket[0])
		{
			whichParam = 0;
		}
		else if (_queryParts.selectingItem == _queryParts.parts[_which].parameteresInBracket[1])
		{
			whichParam = 1;
		}

		for (int i = 0; i < _queryParts.ParametersList.size(); i++)
		{
			if (_queryParts.ParametersList[i].Name == _queryParts.parts[_which].parameteresInBracket[whichParam])
			{
				type = _queryParts.ParametersList[i].Type;
				break;
			}
		}

		if (whichParam == 0)
		{
			if (type == "assign")
			{
				//List<ASSIGN> getUsedBy(VAR v)
			}
			else if (type == "stmt")
			{
				//List<stmt> getUsedBy(VAR v)
			}
			else if (type == "proc")
			{
				//List<proc> getUsedBy(VAR v)
			}
		}

	}
}

