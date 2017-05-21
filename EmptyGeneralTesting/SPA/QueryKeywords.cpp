#include "QueryKeywords.h"

QueryKeywords::QueryKeywords() {
}

QueryKeywords::~QueryKeywords() {
}

const string QueryKeywords::SELECT = "Select";
const string QueryKeywords::SUCH = "such";
const string QueryKeywords::THAT = "that";
const string QueryKeywords::AND = "and";
const string QueryKeywords::BOOLEAN = "BOOLEAN";

bool QueryKeywords::isQueryKeyword(string value) {
	return value == SELECT ||
			value == SUCH ||
			value == THAT ||
			value == AND ||
			value == BOOLEAN;
}
