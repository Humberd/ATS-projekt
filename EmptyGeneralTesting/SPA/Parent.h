#include <vector>
#include "STMT.h"
#include "../SPA/SourceFileManager.h"
#include "../SPA/Lexer.h"
#include "../SPA/SourceParser.h"
#include "../SPA/ProgramLineEvaluator.h"
#include <algorithm>
#include <map>
using namespace std;

class Parent
{
	public:
		Parent(map<int, vector<int>> intTable, map<int, vector<Node*>> stmtTable);
		void setParent(STMT s1, STMT s2);
		vector<STMT*> getParent(STMT* s, bool goDeep);
		vector<STMT*> getParentOf(STMT* s, bool goDeep);
		bool isParent(STMT* s1, STMT* s2, bool goDeep);
		static Parent *getInstance( map<int,vector<int>> intTable ,map<int,vector<Node*>> stmtTable );
	private:
		static Parent *instance;
		vector<vector<Node*>> parentTable;
		Node* mainNode;
		vector<STMT*> getParentWithoutDeep(STMT* s);
		vector<STMT*> getParentWithDeep(STMT* s);
		vector<STMT*> getParentOfWithoutDeep(STMT* s);
		vector<STMT*> getParentOfWithDeep(STMT* s);
		map<int,vector<int>> parentMap;
		map<int, vector<Node*>> statementTable;
		bool isParentWithoutDeep(STMT* s1, STMT* s2);
		bool isParentWithDeep(STMT* s1, STMT* s2);
		void FillParentTable();
		
};
