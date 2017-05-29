#include "QueryVariablesValidatorException.h"

QueryVariablesValidatorException::QueryVariablesValidatorException(char const* _Message) : exception(_Message) {
}

QueryVariablesValidatorException::QueryVariablesValidatorException(string& _Message) : exception(_Message.c_str()) {
}

QueryVariablesValidatorException::QueryVariablesValidatorException(string const& _Message) : exception(_Message.c_str()) {
}
