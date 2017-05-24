#pragma once
#include <string>

using namespace std;

class QueryEvaluatorException: public exception {
	explicit QueryEvaluatorException(char const* _Message);

	explicit QueryEvaluatorException(string& _Message);

	explicit QueryEvaluatorException(string const& _Message);
};
