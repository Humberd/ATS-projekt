#pragma once
#include "VariableParser.h"

class QParsingEntity;

class QParsersRepository {
public:
	VariableParser* variableParser;

	QParsersRepository();
	~QParsersRepository();
};
