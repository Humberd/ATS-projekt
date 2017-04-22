#pragma once
#include "ParsingEntity.h"

class ParsingEntity;

class ParsersRepository {
public:
	ParsingEntity* expressionParser;
	ParsingEntity* assignParser;
	ParsingEntity* callParser;

	ParsersRepository();
	~ParsersRepository();
};
