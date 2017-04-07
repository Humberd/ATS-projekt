#include "Constants.h"
#include <vector>

using namespace std;

class Follows
{
	public:
		void setFollows(STMT s1, STMT s2);
		vector<STMT> getFollows(STMT s, bool goDeep);
		vector<STMT> getFollowsBy(STMT s, bool goDeep);
		bool isFollows(STMT s1, STMT s2, bool goDeep);
		bool isFollowsBy(STMT s1, STMT s2, bool goDeep);
	
	private:

};
