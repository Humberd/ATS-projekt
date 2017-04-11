#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
using namespace std;
class CallsTag
{
public:
	CallsTag(QueryParts queryParts);
	~CallsTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;

};

