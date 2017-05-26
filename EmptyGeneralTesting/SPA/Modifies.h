
#include <vector>
#include <map>
#include "STMT.h"
#include "PROC.h"
#include "VAR.h"

using namespace std;

class Modifies
{
private:
	map<int, vector<VAR*>> modifiesSTMT;
	map<string, vector<VAR*>> modifiesPROC;
	static Modifies *instance;

public:
	static Modifies *getInstance();
	Modifies();
	~Modifies();
	void setModifies(STMT* s, VAR* v);
	void setModifies(PROC* p, VAR* v);
	vector<STMT*> getModifiesSTMT(VAR* v);
	vector<PROC*> getModifiesPROC(VAR* v);
	vector<VAR*> getModifiesBy(STMT* s);
	vector<VAR*> getModifiesBy(PROC* p);
	bool isModifies(int s, VAR* v);
	bool isModifies(string p, VAR* v);

};
