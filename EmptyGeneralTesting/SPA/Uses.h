#include <vector>
#include <map>
#include "STMT.h"
#include "VAR.h"
#include "ASSIGN.h"
#include "PROC.h"

using namespace std;

class Uses {
private:
	//map<ASSIGN, vector<VAR>> usesASSIGN;
	//map<STMT, vector<VAR>> usesSTMT;
	//map<PROC, vector<VAR>> usesPROC;
	map<int, vector<VAR*>> usesASSIGN;
	map<int, vector<VAR*>> usesSTMT;
	map<string, vector<VAR*>> usesPROC;
	static Uses *instance;

public:
	static Uses *getInstance();
	Uses();
	~Uses();
	void setUses(ASSIGN* a, VAR* v);
	void setUses(STMT* s, VAR* v);
	void setUses(PROC* p, VAR* v);
	vector<VAR*> getUses(ASSIGN* a);
	vector<VAR*> getUses(STMT* s);
	vector<VAR*> getUses(PROC* p);
	vector<ASSIGN*> getUsedByASSIGN(VAR* v);
	vector<STMT*> getUsesBySTMT(VAR* v);
	vector<PROC*> getUsesByPROC(VAR* v);
	bool isUsed(ASSIGN* a, VAR* v);
	bool isUsed(STMT* s, VAR* v);
	bool isUsed(PROC* p, VAR* v);
};