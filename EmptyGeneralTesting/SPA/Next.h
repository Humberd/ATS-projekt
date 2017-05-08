#include <vector>
#include "STMT.h"

using namespace std;

class Next {

	//map<int, vector<STMT*>> nextMap;

	public:
		void setNext(STMT s1, STMT s2);
		vector<STMT> goNext(STMT s1, bool goDeep);
		vector<STMT> goPrevious(STMT s, bool goDeep);
		bool isNext(STMT s1, STMT s2, bool goDeep);
};