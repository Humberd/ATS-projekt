#pragma once
#include <list>
#include <vector>

using namespace std;

class ResponseParser {
public:
	explicit ResponseParser();
	~ResponseParser();

	static list<string> parse(vector<vector<string>> originalResponse);

	static string parseForTestingPurposes(list<string>& responseList);
};
