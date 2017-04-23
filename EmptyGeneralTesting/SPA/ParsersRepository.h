#pragma once
#include "ParsingEntity.h"

class ParsingEntity;

class ParsersRepository {
public:
	ParsingEntity* expressionParser;
	ParsingEntity* assignParser;
	ParsingEntity* callParser;
	ParsingEntity* whileParser;
	ParsingEntity* ifParser;
	ParsingEntity* statementListParser;
	ParsingEntity* procedureParser;
	ParsingEntity* programParser;

	ParsersRepository();
	~ParsersRepository();
};
