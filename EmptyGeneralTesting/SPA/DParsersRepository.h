#pragma once

class DParsingEntity;

class DParsersRepository {
public:
	DParsingEntity* declarationParser;

	DParsersRepository();
	~DParsersRepository();
};