#include "AffectsTag.h"
#include "../SPA/Affects.h"

AffectsTag::AffectsTag(QueryParts queryParts)
{
	_queryParts = queryParts;
}

AffectsTag::~AffectsTag()
{
}

list<string> AffectsTag::DoQuery()
{
	Affects affects;
	list<string> finalResult;
	if (_queryParts.parameters.size() == 2 && _queryParts.selectingItem != "boolean")
	{
		STMT s1;
		vector<STMT> result;
		if (_queryParts.selectingItem == _queryParts.parameteresInBracket[0])
		{
			if (_queryParts.parameters[0][0] != _queryParts.selectingItem)
			{
				string valToInt = _queryParts.parameters[0][1];
				s1 = stoi(valToInt);

				if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
				{
					//result = affects.getAffects(s1, true);
				}
				else
				{
					//result = affects.getAffects(s1, false);
				}
			}
			else if (_queryParts.parameters[1][0] != _queryParts.selectingItem)
			{
				string valToInt = _queryParts.parameters[1][1];
				s1 = stoi(valToInt);

				if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
				{
					//result = affects.getAffectsBy(s1, true);
				}
				else
				{
					//result = affects.getAffectsBy(s1, false);
				}
			}

			for each (int var in result)
			{
				finalResult.push_back(to_string(var));
			}
		}
	}

	else if (_queryParts.parameters.size() == 2 && _queryParts.selectingItem == "boolean")
	{
		STMT s1;
		STMT s2;
		string valToInt = _queryParts.parameters[0][1];
		s1 = stoi(valToInt);
		valToInt = _queryParts.parameters[1][1];
		s2 = stoi(valToInt);
		bool boolResult;
		if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
		{
			//boolResult = affects.ifAffects(s1, s2, true);
		}
		else
		{
			//boolResult = affects.ifAffects(s1, s2, false);
		}
		finalResult.push_back(to_string(boolResult));
	}
	return finalResult;
}
