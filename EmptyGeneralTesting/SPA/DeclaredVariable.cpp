#include "DeclaredVariable.h"

DeclaredVariable::DeclaredVariable() {
}

DeclaredVariable::~DeclaredVariable() {
	
}

string DeclaredVariable::getType() const {
	return type;
}

void DeclaredVariable::setType(const string type) {
	this->type = type;
}

string DeclaredVariable::getName() const {
	return name;
}

void DeclaredVariable::setName(const string name) {
	this->name = name;
}

