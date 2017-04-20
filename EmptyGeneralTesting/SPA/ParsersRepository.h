#pragma once
#include "ParsingEntity.h"

class ParsingEntity;

class ParsersRepository {
public:
	ParsingEntity* expressionParser;

	ParsersRepository();
	~ParsersRepository();
};
