#pragma once
#include "DParsersRepository.h"
#include <vector>
#include "QLexerToken.h"
#include "DeclaredVariable.h"

using namespace std;

class DeclarationsSourceParser {
private:
	DParsersRepository* parsersRepo;
	vector<QLexerToken*>& tokensList;
	vector<QLexerToken*>::iterator iterator;
	vector<QLexerToken*>::iterator iteratorEnd;



public:
	explicit DeclarationsSourceParser(vector<QLexerToken*>& tokensList);
	~DeclarationsSourceParser();
	vector<DeclaredVariable*> parse() const;
};
