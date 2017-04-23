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
	CallsTag(QueryParts queryParts,int which);
	~CallsTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
	int _which;

};

