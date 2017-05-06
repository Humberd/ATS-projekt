#include <vector>
#include "STMT.h"

using namespace std;

class Parent
{
	public:
		void setParent(STMT s1, STMT s2);
		vector<STMT> getParent(STMT s, bool goDeep);
		vector<STMT> getParentOf(STMT s, bool goDeep);
		bool isParent(STMT s1, STMT s2, bool goDeep);

	private:

};
