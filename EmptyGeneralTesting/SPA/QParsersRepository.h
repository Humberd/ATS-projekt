#pragma once
#include "VariableParser.h"
#include "MethodParser.h"
#include "WithParser.h"
#include "WithManyParser.h"
#include "MethodManyParser.h"
#include "SelectParser.h"

class QParsingEntity;

class QParsersRepository {
public:
	SelectParser* selectParser;
	VariableParser* variableParser;
	MethodParser* methodParser;
	MethodManyParser* methodManyParser;
	WithParser* withParser;
	WithManyParser* withManyParser;

	QParsersRepository();
	~QParsersRepository();
};
