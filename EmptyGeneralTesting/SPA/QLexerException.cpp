#include "QLexerException.h"

QLexerException::QLexerException(char const* _Message) : exception(_Message) {
}

QLexerException::QLexerException(string& _Message) : exception(_Message.c_str()) {
}

QLexerException::QLexerException(string const& _Message) : exception(_Message.c_str()) {
}
