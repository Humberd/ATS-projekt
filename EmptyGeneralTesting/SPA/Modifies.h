
#include "Constants.h"
#include <vector>

using namespace std;

class Modifies
{
public:
	void setModifies(STMT s, VAR v);
	void setModifies(PROC p, VAR v);
	vector<STMT> getModifiesSTMT(VAR v);
	vector<PROC> getModifiesPROC(VAR v);
	vector<VAR> getModifiesBy(STMT s);
	vector<VAR> getModifiesBy(PROC p);
	bool isModifies(STMT s, VAR v);
	bool isModifies(PROC p, VAR v);

private:

};
