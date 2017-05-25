#pragma once
#include <map>
#include <vector>
#include "Node.h"

using namespace std;

class SpaDataContainer {
public:
	explicit SpaDataContainer();
	~SpaDataContainer();

	Node* rootNode;

	/*Parent*/
	map<int, vector<int>> parentsTable;

	/*Follows*/
	map<int, vector<int>> followsTable;

	/*Uses*/
	/*statements to variable names*/
	map<int, vector<string>> usesStatementTable;
	/*Procedures to variable names*/
	map<string, vector<string>> usesProcedureTable;

	/*Modifies*/
	/*Statements to variable names*/
	map<int, vector<int>> modifiesStatementTable;
	/*Procedures to variable names*/
	map<string, vector<string>> modifiesProcedureTable;

	/*Calls*/
	/*Procedures to variable names*/
	map<string, vector<string>> callsTable;

	/*.........................................*/
	/*Helper tables to prevent unneccessary AST traversing*/

	/*Maps programLineNumber to a list of Nodes with that programLineNumber*/
	map<int, vector<Node*>> statementTable;

	/*A list of program procedures*/
	vector<Node*> proceduresTable;
};
