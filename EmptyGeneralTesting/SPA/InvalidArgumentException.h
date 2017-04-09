#pragma once
#include "ASTException.h"

class InvalidArgumentException : public ASTException {

public:
	explicit InvalidArgumentException(Node* node, char const* _Message);

	explicit InvalidArgumentException(Node* node, string& _Message);

	explicit InvalidArgumentException(Node* node, string const& _Message);
};
