#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <list>
#include "QueryParts.h"
using namespace std;
class AffectsTag
{
public:
	AffectsTag(QueryParts queryParts);
	~AffectsTag();
	list<string> DoQuery();
private:
	QueryParts _queryParts;
};

