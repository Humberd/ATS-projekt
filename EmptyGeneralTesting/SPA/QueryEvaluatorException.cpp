#include "QueryEvaluatorException.h"

QueryEvaluatorException::QueryEvaluatorException(char const* _Message) : exception(_Message) {
}

QueryEvaluatorException::QueryEvaluatorException(string& _Message) : exception(_Message.c_str()) {
}

QueryEvaluatorException::QueryEvaluatorException(string const& _Message) : exception(_Message.c_str()) {
}
