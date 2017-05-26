#include <vector>
#include "ASSIGN.h"

using namespace std;

class Affects {
	public:
		vector<ASSIGN> getAffects(ASSIGN a, bool goDeep);
		vector<ASSIGN> getAffectsBy(ASSIGN a, bool goDeep);
		bool ifAffects(ASSIGN a1, ASSIGN a2, bool goDeep);
};