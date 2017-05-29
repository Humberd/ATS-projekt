#include "TreeAnalyzerException.h"

TreeAnalyzerException::TreeAnalyzerException(char const* _Message) : exception(_Message) {
}

TreeAnalyzerException::TreeAnalyzerException(string& _Message) : exception(_Message.c_str()) {
}

TreeAnalyzerException::TreeAnalyzerException(string const& _Message) : exception(_Message.c_str()) {
}
