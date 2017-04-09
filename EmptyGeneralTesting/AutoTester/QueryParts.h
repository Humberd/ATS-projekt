using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <algorithm>



class QueryParts
{
public:
	QueryParts();
	~QueryParts();
	vector<vector<string>> parameters;
	string tag;
	string selectingItem;
	vector<string> parameteresInBracket;
};
