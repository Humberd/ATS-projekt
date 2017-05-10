#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
class ParentTag
{
public:
	ParentTag(QueryParts queryParts, int which);
	~ParentTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
	int _which;
};

