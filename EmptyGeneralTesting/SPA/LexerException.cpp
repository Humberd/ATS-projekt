#include "LexerException.h"

LexerException::LexerException(char const* _Message) : exception(_Message) {
}

LexerException::LexerException(string& _Message) : exception(_Message.c_str()) {
}

LexerException::LexerException(string const& _Message) : exception(_Message.c_str()) {
}
