#include "QueryMethods.h"

QueryMethods::QueryMethods() {
}

QueryMethods::~QueryMethods() {
}

const string QueryMethods::PARENT = "Parent";
const string QueryMethods::FOLLOWS = "Follows";
const string QueryMethods::USES = "Uses";
const string QueryMethods::CALLS = "Calls";
const string QueryMethods::NEXT = "Next";
const string QueryMethods::MODIFIES = "Modifies";
const string QueryMethods::AFFECTS = "Affects";
const string QueryMethods::PATTERN = "pattern";

bool QueryMethods::isQueryMethod(string value) {
	return value == PARENT ||
			value == FOLLOWS ||
			value == USES ||
			value == CALLS ||
			value == NEXT ||
			value == MODIFIES ||
			value == AFFECTS ||
			value == PATTERN;
}
