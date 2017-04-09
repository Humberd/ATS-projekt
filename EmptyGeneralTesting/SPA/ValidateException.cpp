#include "ValidateException.h"

ValidateException::ValidateException(Node* node, char const* _Message) : ASTException(node, _Message) {
}

ValidateException::ValidateException(Node* node, string& _Message) : ASTException(node, _Message) {
}

ValidateException::ValidateException(Node* node, string const& _Message): ASTException(node, _Message) {
}
