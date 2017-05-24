#pragma once
#include <string>

using namespace std;

class QueryEvaluatorException: public exception {
public:
	explicit QueryEvaluatorException(char const* _Message);

	explicit QueryEvaluatorException(string& _Message);

	explicit QueryEvaluatorException(string const& _Message);
};
