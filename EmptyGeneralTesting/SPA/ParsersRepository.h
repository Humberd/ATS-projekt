#pragma once
#include "ParsingEntity.h"

class ParsersRepository {
public:
	ParsersRepository();
	~ParsersRepository();

	ParsingEntity* expressionParser;
};
