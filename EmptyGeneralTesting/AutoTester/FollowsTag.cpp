#include "FollowsTag.h"
#include "../SPA/Follows.h"


FollowsTag::FollowsTag(QueryParts queryParts)
{
	_queryParts = queryParts;
}


FollowsTag::~FollowsTag()
{
}

list<string> FollowsTag::DoQuery()
{
	Follows follows;
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
					result = follows.getFollows(s1, true);
				}
				else
				{
					result = follows.getFollows(s1, false);
				}
			}
			else if (_queryParts.parameters[1][0] != _queryParts.selectingItem)
			{
				string valToInt = _queryParts.parameters[1][1];
				s1 = stoi(valToInt);

				if (_queryParts.tag.substr(_queryParts.parameteresInBracket[1].size() - 1, 1) == "*")
				{
					result = follows.getFollowsBy(s1, true);
				}
				else
				{
					result = follows.getFollowsBy(s1, false);
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
			boolResult = follows.isFollows(s1, s2, true);
		}
		else
		{
			boolResult = follows.isFollows(s1, s2, false);
		}
		finalResult.push_back(to_string(boolResult));
	}


	return finalResult;
}
