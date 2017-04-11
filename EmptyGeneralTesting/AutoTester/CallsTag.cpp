#include "CallsTag.h"
#include "../SPA/Calls.h"



CallsTag::CallsTag(QueryParts queryParts)
{
	_queryParts = queryParts;
}


CallsTag::~CallsTag()
{
}

list<string> CallsTag::DoQuery()
{
	Calls calls;
	list<string> finalResult;
	if (_queryParts.parameters.size() == 2 && _queryParts.selectingItem != "boolean")
	{
		PROC p1;
		vector<PROC> result;
		if (_queryParts.selectingItem == _queryParts.parameteresInBracket[0])
		{
			if (_queryParts.parameteresInBracket[0][0] == '"' && _queryParts.parameteresInBracket[0][_queryParts.parameteresInBracket[0].size() - 1] == '"')
			{
				p1 = _queryParts.parameteresInBracket[0].substr(1, _queryParts.parameteresInBracket[0].size() - 2);
			}
			else
				p1 = _queryParts.parameteresInBracket[0];
			if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
			{
				//result = calls.getCallsFrom(p1, true);
			}
			else
			{
				//result = calls.getCallsFrom(p1, false);
			}

		}
		else if (_queryParts.selectingItem == _queryParts.parameteresInBracket[1])
		{
			if (_queryParts.parameteresInBracket[1][0] == '"' && _queryParts.parameteresInBracket[1][_queryParts.parameteresInBracket[1].size() - 1] == '"')
			{
				p1 = _queryParts.parameteresInBracket[1].substr(1, _queryParts.parameteresInBracket[1].size() - 2);
			}
			else
				p1 = _queryParts.parameteresInBracket[1];


			if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
			{
				//result = calls.getCalls(p1, true);
			}
			else
			{
				//result = calls.getCalls(p1, false);
			}
		}

		for each (string var in result)
		{
			finalResult.push_back(var);
		}

	}
	if (_queryParts.parameters.size() == 2 && _queryParts.selectingItem == "boolean")
	{
		PROC p1, p2;
		if (_queryParts.parameteresInBracket[0][0] == '"' && _queryParts.parameteresInBracket[0][_queryParts.parameteresInBracket[0].size() - 1] == '"')
		{
			p1 = _queryParts.parameteresInBracket[0].substr(1, _queryParts.parameteresInBracket[0].size() - 2);
		}
		else
			p1 = _queryParts.parameteresInBracket[0];

		if (_queryParts.parameteresInBracket[1][0] == '"' && _queryParts.parameteresInBracket[1][_queryParts.parameteresInBracket[1].size() - 1] == '"')
		{
			p2 = _queryParts.parameteresInBracket[1].substr(1, _queryParts.parameteresInBracket[1].size() - 2);
		}
		else
			p2 = _queryParts.parameteresInBracket[1];
		bool result;// = calls.isCalls(p1, p2);
		finalResult.push_back(to_string(result));
	}
	return finalResult;
}
