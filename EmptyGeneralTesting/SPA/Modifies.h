
#include "Constants.h"
#include <vector>
#include <map>

using namespace std;

class Modifies
{
private:
	map<STMT, vector<VAR>> modifiesSTMT;
	map<PROC, vector<VAR>> modifiesPROC;
	static Modifies *instance;

public:
	static Modifies *getInstance();
	Modifies();
	~Modifies();
	void setModifies(STMT s, VAR v);
	void setModifies(PROC p, VAR v);
	vector<STMT> getModifiesSTMT(VAR v);
	vector<PROC> getModifiesPROC(VAR v);
	vector<VAR> getModifiesBy(STMT s);
	vector<VAR> getModifiesBy(PROC p);
	bool isModifies(STMT s, VAR v);
	bool isModifies(PROC p, VAR v);

};
