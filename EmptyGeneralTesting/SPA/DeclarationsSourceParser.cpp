#include "DeclarationsSourceParser.h"
#include "DeclarationParser.h"
#include <algorithm>
#include "QParserException.h"

DeclarationsSourceParser::DeclarationsSourceParser(vector<QLexerToken*>& tokensList): tokensList(tokensList) {
	iterator = tokensList.begin();
	iteratorEnd = tokensList.end();

	parsersRepo = new DParsersRepository;
	parsersRepo->declarationParser = new DeclarationParser(parsersRepo, iterator, iteratorEnd);
}

DeclarationsSourceParser::~DeclarationsSourceParser() {
	delete parsersRepo;
}

vector<DeclaredVariable*> DeclarationsSourceParser::parse() const {
	vector<DeclaredVariable*> result;

	while (iterator != iteratorEnd) {
		auto variables = parsersRepo->declarationParser->parse();

		for (auto variable : variables) {
			/*Need to check if there is already a variable with the same name*/
			auto anotherVariableWithSameName =
				find_if(result.begin(), result.end(), [variable](DeclaredVariable* item) {
				return variable->getName() == item->getName();
			});

			if (anotherVariableWithSameName != result.end()) {
				throw QParserException("DeclarationsSourceParser - there is already a variable with the name: " + variable->getName());
			} else {
				result.push_back(variable);
			}
		}
	}

	return result;
}
