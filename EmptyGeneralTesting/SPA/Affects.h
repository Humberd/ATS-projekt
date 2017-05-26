#include <vector>
#include "ASSIGN.h"
#include <map>
using namespace std;

class Affects {
	public:
		Affects(map<int, vector<int>> _affectsMap);
		vector<ASSIGN*> getAffects(ASSIGN* a, bool goDeep);
		vector<ASSIGN*> getAffectsBy(ASSIGN* a, bool goDeep);
		bool ifAffects(ASSIGN* a1, ASSIGN* a2, bool goDeep);
		static Affects *getInstance(map<int, vector<int>> _affectsMap);
	private:
		static Affects *instance;
		map<int, vector<int>> affectsMap;
		vector<ASSIGN*> getAffectsWithoutDeep(ASSIGN* a);
		vector<ASSIGN*> getAffectsWithDeep(ASSIGN* a);
		vector<ASSIGN*> getAffectsByWithDeep(ASSIGN* a);
		vector<ASSIGN*> getAffectsByWithoutDeep(ASSIGN* a);
		bool ifAffectsWithoutDeep(ASSIGN* a1, ASSIGN* a2);
		bool ifAffectsWithDeep(ASSIGN* a1, ASSIGN* a2);
};