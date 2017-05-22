#pragma once
#include "VariableParser.h"
#include "MethodParser.h"

class QParsingEntity;

class QParsersRepository {
public:
	VariableParser* variableParser;
	MethodParser* methodParser;

	QParsersRepository();
	~QParsersRepository();
};
