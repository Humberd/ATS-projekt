#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <algorithm>
class Part
{
public:
	Part();
	~Part();
	string tag;
	vector<string> parameteresInBracket;
};

