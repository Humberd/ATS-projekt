#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
class NextTag
{
public:
	NextTag(QueryParts queryParts, int which);
	~NextTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
	int _which;
};

