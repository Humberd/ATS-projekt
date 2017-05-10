#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
class UsesTag
{
public:
	UsesTag(QueryParts queryParts, int which);
	~UsesTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
	int _which;
};

