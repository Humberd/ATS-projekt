#include "QueryVariable.h"

QueryVariable::QueryVariable() {
}

QueryVariable::QueryVariable(string name,
                             string propertyName): name(name), propertyName(propertyName) {
}

QueryVariable::~QueryVariable() {
}

string QueryVariable::getName() const {
	return name;
}

void QueryVariable::setName(const string name) {
	this->name = name;
}

string QueryVariable::getPropertyName() const {
	return propertyName;
}

void QueryVariable::setPropertyName(const string propertyName) {
	this->propertyName = propertyName;
}

string QueryVariable::getType() const {
	return type;
}

void QueryVariable::setType(const string type) {
	this->type = type;
}
