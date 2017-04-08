#include "ValidateException.h"

ValidateException::ValidateException(const string& _Message): exception(_Message.c_str()) {
}

ValidateException::ValidateException(const char* _Message): exception(_Message) {
}
