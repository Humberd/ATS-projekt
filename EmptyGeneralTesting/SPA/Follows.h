#include <vector>
#include <map>
#include "STMT.h"
#include "PROC.h"

using namespace std;

class Follows
{
private:
	map<int, vector<int>> followsTable;

	static Follows *instance;

public:
	static Follows *getInstance(map<int, vector<int>> _map);
	Follows(map<int, vector<int>> _map);
	~Follows();
	void setFollows(STMT* s1, STMT* s2);
	vector<STMT*> getFollows(STMT* s, bool goDeep);
	vector<STMT*> getFollowsBy(STMT* s, bool goDeep);
	bool isFollows(STMT* s1, STMT* s2, bool goDeep);
	bool isFollowsBy(STMT* s1, STMT* s2, bool goDeep);


	vector<STMT*> getFollowsWithoutDeep(STMT* a);
	vector<STMT*> getFollowsWithDeep(STMT* a);
	vector<STMT*> getFollowsByWithDeep(STMT* a);
	vector<STMT*> getFollowsByWithoutDeep(STMT* a);
	bool isFollowsWithoutDeep(STMT* a1, STMT* a2);
	bool isFollowsWithDeep(STMT* a1, STMT* a2);
	bool isFollowsByWithoutDeep(STMT* a1, STMT* a2);
	bool isFollowsByWithDeep(STMT* a1, STMT* a2);

};
