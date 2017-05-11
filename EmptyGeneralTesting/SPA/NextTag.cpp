#include "NextTag.h"
#include "../SPA/Next.h"

NextTag::NextTag(QueryParts queryParts, int which)
{
	_queryParts = queryParts;
	_which = which;
}


NextTag::~NextTag()
{
}


list<string> NextTag::DoQuery()
{
	Next next;
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
			//next.isNext(s1, s2,InDepth);
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
			//helpOutput = next.goNext(s1, InDepth);
		}
		else if (std::find_if(par2.begin(), par2.end(), isdigit) != par2.end())
		{
			s1 = new STMT(stoi(par2));
			//helpOutput = next.goPrevious(s1, InDepth);
		}
		for each (STMT* var in helpOutput)
		{
			finalResult.push_back(to_string(var->getSTMT()));
		}
	}
}