#include "Constants.h"
#include <vector>
#include <map>

using namespace std;

class Follows
{
private:
	map<STMT, vector<STMT>> followsTable;

	static Follows *instance;
	vector<PROC> getFollows(STMT s);
	vector<PROC> getFollowsDeep(STMT s);
	vector<PROC> getFollowsBy(STMT s);
	vector<PROC> getFollowsDeepBy(STMT s);

public:
	static Follows *getInstance();
	Follows();
	~Follows();
	void setFollows(STMT s1, STMT s2);
	vector<STMT> getFollows(STMT s, bool goDeep);
	vector<STMT> getFollowsBy(STMT s, bool goDeep);
	bool isFollows(STMT s1, STMT s2, bool goDeep);
	bool isFollowsBy(STMT s1, STMT s2, bool goDeep);
};
