#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(Node* node, char const* _Message) : ASTException(node, _Message) {

}

InvalidArgumentException::InvalidArgumentException(Node* node, string& _Message) : ASTException(node, _Message) {
}
