#include "FollowsTag.h"
//#include "../SPA/Follows.h"


FollowsTag::FollowsTag(QueryParts queryParts,int which)
{
	_queryParts = queryParts;
	_which = which;
}


FollowsTag::~FollowsTag()
{
}

list<string> FollowsTag::DoQuery()
{
	list<string> finalResult;
	/*
	Follows follows;
	list<string> finalResult;

	vector<STMT*> helpOutput;
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
		STMT* s1;
		STMT* s2;
		string par = _queryParts.parts[_which].parameteresInBracket[0];
		string par2 = _queryParts.parts[_which].parameteresInBracket[1];
		if ((std::find_if(par.begin(), par.end(), isdigit) != par.end()) && (std::find_if(par2.begin(), par2.end(), isdigit) != par2.end()))
		{
			s1 = new STMT(stoi(par));
			s2 = new STMT(stoi(par2));
			bool output = false;
			//= follows.isFollows(s1, s2, InDepth);
			finalResult.push_back(to_string(output));
		}
	}
	else
	{
		STMT* s1;
		string par = _queryParts.parts[_which].parameteresInBracket[0];
		string par2 = _queryParts.parts[_which].parameteresInBracket[1];
		if (std::find_if(par.begin(), par.end(), isdigit) != par.end())
		{
			s1 = new STMT(stoi(par));
			//helpOutput = follows.getFollows(s1, InDepth);
		}
		else if (std::find_if(par2.begin(), par2.end(), isdigit) != par2.end())
		{
			s1 = new STMT(stoi(par2));
			//helpOutput = follows.getFollowsBy(s1, InDepth);
		}
		for each (STMT* var in helpOutput)
		{
			finalResult.push_back(to_string(var->getSTMT()));
		}
	}
	*/


	/*
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
					//result = follows.getFollows(s1, true);
				}
				else
				{
					//result = follows.getFollows(s1, false);
				}
			}
			else if (_queryParts.parameters[1][0] != _queryParts.selectingItem)
			{
				string valToInt = _queryParts.parameters[1][1];
				s1 = stoi(valToInt);

				if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
				{
					//result = follows.getFollowsBy(s1, true);
				}
				else
				{
					//result = follows.getFollowsBy(s1, false);
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
			//boolResult = follows.isFollows(s1, s2, true);
		}
		else
		{
			//boolResult = follows.isFollows(s1, s2, false);
		}
		finalResult.push_back(to_string(boolResult));
	}

	*/
	return finalResult;
}
