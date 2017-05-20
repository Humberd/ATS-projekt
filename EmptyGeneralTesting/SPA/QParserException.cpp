#include "QParserException.h"

QParserException::QParserException(char const* _Message) : exception(_Message) {
}

QParserException::QParserException(string& _Message) : exception(_Message.c_str()) {
}

QParserException::QParserException(string const& _Message) : exception(_Message.c_str()) {
}
