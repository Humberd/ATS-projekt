#include "ResponseParser.h"

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
