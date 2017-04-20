#include "ExpressionParser.h"
#include "ExpressionNode.h"
#include "rx.hpp"
#include "rx-subscriber.hpp"
#include <CppUnitTestLogger.h>

namespace Rx {
	using namespace rxcpp;
	using namespace rxcpp::sources;
	using namespace rxcpp::operators;
	using namespace rxcpp::util;
}

using namespace Rx;

ExpressionParser::ExpressionParser(ParsersRepository* parsersRepo,
                                   vector<LexerToken*>::iterator& iterator,
                                   vector<LexerToken*>::iterator& iteratorEnd): ParsingEntity(parsersRepo, iterator, iteratorEnd) {
}

ExpressionParser::~ExpressionParser() {
}

Node* ExpressionParser::parse() {
	sources::range(0, 1000)
			.take(5)
			.filter([](int val) {
					return val < 100;
				})
			.subscribe([](int val) {
					Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("dupa");
				});
	return nullptr;
}
