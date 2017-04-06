#include "Constants.h"
#include <vector>

using namespace std;

class Uses {
	public:
		void setUses(ASSIGN a, VAR v);
		void setUses(STMT s, VAR v);
		void setUses(PROC p, VAR v);
		vector<VAR> getUses(ASSIGN a);
		vector<VAR> getUses(STMT s);
		vector<VAR> getUses(PROC p);
		vector<ASSIGN> getUsedByASSIGN(VAR v);
		vector<STMT> getUsesBySTMT(VAR v);
		vector<PROC> getUsesByPROC(VAR v);
		bool isUsed(ASSIGN a, VAR v);
		bool isUsed(STMT s, VAR v);
		bool isUsed(PROC p, VAR v);
};