#pragma once
#include <exception>
#include <string>
#include "ASTException.h"

using namespace std;

class ValidateException : public ASTException
{
public:
	explicit ValidateException(Node* node, char const* _Message);

	explicit ValidateException(Node* node, string& _Message);

	explicit ValidateException(Node* node, string const& _Message);
};

