#pragma once
#include <string>

using namespace std;

class QueryKeywords {
private:
	QueryKeywords();
	~QueryKeywords();

public:
	static const string SELECT;
	static const string SUCH;
	static const string THAT;
	static const string AND;
	static const string BOOLEAN;

	static bool isQueryKeyword(string value);
};
