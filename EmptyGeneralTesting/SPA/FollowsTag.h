#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
using namespace std;
class FollowsTag
{
public:
	FollowsTag(QueryParts queryParts,int _which);
	~FollowsTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
	int _which;
};

