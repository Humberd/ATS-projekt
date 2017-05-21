#include "DeclaredVariable.h"

DeclaredVariable::DeclaredVariable(string type, string name) : type(type),
                                                               name(name) {
}

DeclaredVariable::~DeclaredVariable() {
	
}

string DeclaredVariable::getType() const {
	return type;
}

string DeclaredVariable::getName() const {
	return name;
}

