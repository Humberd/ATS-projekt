#include <vector>
#include "STMT.h"
#include <map>
using namespace std;

class Next {

public:
	Next(map<int, vector<int>> _affectsMap);
	vector<STMT*> goNext(STMT* a, bool goDeep);
	vector<STMT*> goPrevious(STMT* a, bool goDeep);
	bool isNext(Next* a1, STMT* a2, bool goDeep);
	static Next *getInstance(map<int, vector<int>> _affectsMap);
private:
	static Next *instance;
	map<int, vector<int>> affectsMap;
	vector<STMT*> goNextWithoutDeep(STMT* a);
	vector<STMT*> goNextWithDeep(STMT* a);
	vector<STMT*> goNextByWithDeep(STMT* a);
	vector<STMT*> goNextByWithoutDeep(STMT* a);
	bool isNextWithoutDeep(STMT* a1, STMT* a2);
	bool isNextWithDeep(STMT* a1, STMT* a2);

};