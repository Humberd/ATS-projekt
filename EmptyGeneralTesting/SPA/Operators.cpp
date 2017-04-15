#include "Operators.h"

Operators::Operators() {
}

Operators::~Operators() {
}

const string Operators::PLUS_SIGN = "+";
const string Operators::MINUS_SIGN = "-";
const string Operators::TIMES_SIGN = "*";

bool Operators::isOperator(string value) {
	return value == PLUS_SIGN ||
			value == MINUS_SIGN ||
			value == TIMES_SIGN;
}

bool Operators::isOperator(char value) {
	return isOperator(string(1, value));
}
