#include "SourceFileException.h"

SourceFileException::SourceFileException(char const* _Message): exception(_Message) {
}

SourceFileException::SourceFileException(string& _Message): exception(_Message.c_str()) {
}

SourceFileException::SourceFileException(string const& _Message): exception(_Message.c_str()) {
}
