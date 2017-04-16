#include "ParserException.h"

ParserException::ParserException(char const* _Message) : exception(_Message) {
}

ParserException::ParserException(string& _Message) : exception(_Message.c_str()) {
}

ParserException::ParserException(string const& _Message) : exception(_Message.c_str()) {
}

ParserException::ParserException(Printable* printable) : exception(printable->toString().c_str()) {

}
