#pragma once
#pragma once
#include "../SPA/Node.h"
#include "../SPA/ParsingEntity.h"

class ParsersRepository;

class ProcedureParserMock : public ParsingEntity {
public:
	explicit ProcedureParserMock(ParsersRepository* parsersRepo,
	                             vector<LexerToken*>::iterator& iterator,
	                             vector<LexerToken*>::iterator& iteratorEnd);
	~ProcedureParserMock();

	Node* parse() override;
};
