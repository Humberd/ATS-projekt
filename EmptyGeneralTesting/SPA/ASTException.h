#pragma once
#include <exception>
#include "Node.h"


using namespace std;

class ASTException : public exception {
private:
	Node* node;

	/*It returns a string in this format:
	* <ClassName> at line: <lineNumber> -
	* For example:
	* ProcedureNode at line: 5 -
	*/
	string errorMessage() const;
public:

	explicit ASTException(Node* node, char const* _Message);

	explicit ASTException(Node* node, string& _Message);

	char const* what() const override;
};