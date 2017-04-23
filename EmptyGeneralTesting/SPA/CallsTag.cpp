#include "CallsTag.h"
#include "../SPA/Calls.h"



CallsTag::CallsTag(QueryParts queryParts,int which)
{
	_queryParts = queryParts;
	_which = which;
}


CallsTag::~CallsTag()
{
}

list<string> CallsTag::DoQuery()
{
	Calls calls;
	list<string> finalResult;
	vector<string> helpOutput;
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
		PROC p1= _queryParts.parametersWithVector[0].Name.substr(1, _queryParts.parametersWithVector[0].Name.size()-2);
		PROC p2= _queryParts.parametersWithVector[1].Name.substr(1, _queryParts.parametersWithVector[1].Name.size() - 2);
		string par = _queryParts.parts[_which].parameteresInBracket[0] + ".";
		bool exists = _queryParts.parametersWithVector[0].Type.find(par) != std::string::npos;
		bool output;
		if (exists)
		{		
			output=calls.isCalls(p1, p2);
		}
		else
		{
			output = calls.isCalls(p2, p1);
		}
		finalResult.push_back(to_string(output));
	}
	else
	{
		if (_queryParts.parts[_which].parameteresInBracket[0][0] == '"' && _queryParts.parts[_which].parameteresInBracket[0][_queryParts.parts[_which].parameteresInBracket[0].size() - 1] == '"')
		{
			PROC p;
			p = _queryParts.parts[_which].parameteresInBracket[0].substr(1, _queryParts.parts[_which].parameteresInBracket[0].size() - 2);
			helpOutput =calls.getCalls(p, InDepth);
		}
		else if (_queryParts.parts[_which].parameteresInBracket[1][0] == '"' && _queryParts.parts[_which].parameteresInBracket[1][_queryParts.parts[_which].parameteresInBracket[1].size() - 1] == '"')
		{
			PROC p;
			p = _queryParts.parts[_which].parameteresInBracket[1].substr(1, _queryParts.parts[_which].parameteresInBracket[1].size() - 2);
			helpOutput = calls.getCallsFrom(p, InDepth);
		}
		for each (string var in helpOutput)
		{
			finalResult.push_back(var);
		}
	}

	/*
	if (_queryParts.parameteresInBracket.size() == 2 && _queryParts.selectingItem != "boolean")
	{
		PROC p1;
		vector<PROC> result;
		string checkBool = _queryParts.tag.substr(_queryParts.tag.size() - 1, 1);
		if (_queryParts.selectingItem == _queryParts.parameteresInBracket[0])
		{
			if (_queryParts.parameteresInBracket[0][0] == '"' && _queryParts.parameteresInBracket[0][_queryParts.parameteresInBracket[0].size() - 1] == '"')
			{
				p1 = _queryParts.parameteresInBracket[0].substr(1, _queryParts.parameteresInBracket[0].size() - 2);
			}
			else if (_queryParts.parameteresInBracket[1][0] == '"' && _queryParts.parameteresInBracket[1][_queryParts.parameteresInBracket[0].size() - 1] == '"')
			{
				p1 = _queryParts.parameteresInBracket[1].substr(1, _queryParts.parameteresInBracket[1].size() - 2);
				//p1 = _queryParts.parameteresInBracket[0];
			}
			
			if (checkBool == "*")
			{
				result = calls.getCallsFrom(p1, true);
			}
			else
			{
				result = calls.getCallsFrom(p1, false);
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


			if (checkBool == "*")
			{
				result = calls.getCalls(p1, true);
			}
			else
			{
				result = calls.getCalls(p1, false);
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
		bool result = calls.isCalls(p1, p2);
		finalResult.push_back(to_string(result));
	}
	*/

	return finalResult;
}
