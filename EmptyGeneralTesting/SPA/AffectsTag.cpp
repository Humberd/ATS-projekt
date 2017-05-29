#include "AffectsTag.h"
#include "../SPA/Affects.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

AffectsTag::AffectsTag(QueryParts queryParts, int which)
{
	_queryParts = queryParts;
	_which = which;
}

AffectsTag::~AffectsTag()
{
}

list<string> AffectsTag::DoQuery()
{
	list<string> finalResult;
	/*
	Affects affects;
	list<string> finalResult;
	vector<ASSIGN*> helpOutput;
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
		ASSIGN* s1;
		ASSIGN* s2;
		string par = _queryParts.parts[_which].parameteresInBracket[0];
		string par2 = _queryParts.parts[_which].parameteresInBracket[1];
		if ((std::find_if(par.begin(), par.end(), isdigit) != par.end()) && (std::find_if(par2.begin(), par2.end(), isdigit) != par2.end()))
		{
			s1 = new ASSIGN(stoi(par));
			s2 = new ASSIGN(stoi(par2));
			//bool output = affects.ifAffects(s1, s2,InDepth);
			//finalResult.push_back(to_string(output));
		}
	}
	else
	{
		ASSIGN* s1;
		string par = _queryParts.parts[_which].parameteresInBracket[0];
		string par2 = _queryParts.parts[_which].parameteresInBracket[1];
		if (std::find_if(par.begin(), par.end(), isdigit) != par.end())
		{
			s1 = new ASSIGN(stoi(par));
			//helpOutput=affects.getAffects(s1, InDepth);
		}
		else if (std::find_if(par2.begin(), par2.end(), isdigit) != par2.end())
		{
			s1 = new ASSIGN(stoi(par2));
			//helpOutput=affects.getAffectsBy(s1, InDepth);
		}
		for each (ASSIGN* var in helpOutput)
		{
			finalResult.push_back(to_string(var->getASSIGN()));
		}
		
	}
	*/
	/*
	if (_queryParts.parameteresInBracket.size() == 2 && _queryParts.selectingItem != "boolean")
	{
		STMT s1;
		vector<STMT> result;
		if (_queryParts.selectingItem == _queryParts.parameteresInBracket[0])
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

		else if (_queryParts.selectingItem == _queryParts.parameteresInBracket[1])
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
	*/

	return finalResult;
}

bool String2Int(const std::string& str, int& result)
{
	result = std::atoi(str.c_str());
	return true;
}