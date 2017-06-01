#include "TestWrapper.h"
#include "../../SPA/Spa.h"
//#include <thread>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;

AbstractWrapper* WrapperFactory::createWrapper() {
	if (wrapper == 0) wrapper = new TestWrapper;
	return wrapper;
}

// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
	// create any objects here as instance variables of this class
	// as well as any initialization required for your spa program
}

TestWrapper::~TestWrapper() {
	delete spaDataContainer->rootNode;
	delete spaDataContainer;
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	Node* rootNode = Spa::generateAstFromFile(filename);
	spaDataContainer = Spa::generateHelperTables(rootNode);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
	int selectIndex = query.find("Select");

	string declarations = query.substr(0, selectIndex);
	string queries = query.substr(selectIndex);

	try {
		list<string> myResults = Spa::evaluateExpression(declarations, queries, spaDataContainer);
		results.insert(results.begin(), myResults.begin(), myResults.end());
	} catch (...) {
		results.clear();
		/*Just don't throw any exception in case of an error :( */
	}
}
