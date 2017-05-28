#include "ResponseParser.h"
#include <algorithm>

ResponseParser::ResponseParser() {
}

ResponseParser::~ResponseParser() {
}

list<string> ResponseParser::parse(vector<vector<string>> originalResponse) {
	list<string> response;

	for (auto touple : originalResponse) {
		if (touple.size() == 1) {
			response.push_back(touple.at(0));
			continue;
		}

		string localResult;
		for (unsigned int i = 0; i < touple.size(); i++) {
			if (i == 0) {
				localResult += touple.at(0);
			} else {
				localResult += " " + touple.at(i);
			}
		}

	}

	return response;
}

string ResponseParser::parseForTestingPurposes(list<string>& responseList) {
	responseList.sort([](string& firstItem, string& secondItem) {
			try {
				return stoi(firstItem) < stoi(secondItem);
			} catch(exception&) {
				return false;
			}
		});

	if (responseList.size() == 0) {
		return "none";
	}
	string response = "";
	bool first = true;
	for (auto item : responseList) {
		if (first) {
			response += item;
			first = false;
			continue;
		}

		response += "," + item;
	}
	return response;
}
