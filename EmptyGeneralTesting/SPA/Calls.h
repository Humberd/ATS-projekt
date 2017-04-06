
#include "Constants.h"
#include <vector>

using namespace std;

class Calls
{
	public:
		void setCalls(PROC p, PROC q);
		vector<PROC> getCalls(PROC p, bool goDeep);
		vector<PROC> getCallsFrom(PROC q, bool goDeep);
		bool isCalls(PROC p, PROC q);

	private:

};
