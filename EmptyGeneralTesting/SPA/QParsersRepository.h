#pragma once
#include "VariableParser.h"
#include "MethodParser.h"
#include "WithParser.h"

class QParsingEntity;

class QParsersRepository {
public:
	VariableParser* variableParser;
	MethodParser* methodParser;
	WithParser* withParser;

	QParsersRepository();
	~QParsersRepository();
};
