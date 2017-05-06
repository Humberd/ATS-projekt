//#include "Uses.h"
//
//Uses *Uses::instance = 0;
//
//Uses * Uses::getInstance()
//{
//	if (!instance) {
//		instance = new Uses();
//	}
//
//	return instance;
//}
//
//Uses::Uses()
//{
//}
//
//Uses::~Uses()
//{
//}
//
//void Uses::setUses(ASSIGN a, VAR v)
//{
//	usesASSIGN[a].push_back(v);
//}
//
//void Uses::setUses(STMT s, VAR v)
//{
//	usesSTMT[s].push_back(v);
//}
//
//void Uses::setUses(PROC p, VAR v)
//{
//	usesPROC[p].push_back(v);
//}
//
//vector<VAR> Uses::getUses(ASSIGN a)
//{
//	if (usesASSIGN.count(a) != 0) {
//		return usesASSIGN[a];
//	}
//
//	return vector<VAR>();
//}
//
//vector<VAR> Uses::getUses(STMT s)
//{
//	if (usesSTMT.count(s) != 0) {
//		return usesSTMT[s];
//	}
//
//	return vector<VAR>();
//}
//
//vector<VAR> Uses::getUses(PROC p)
//{
//	if (usesPROC.count(p) != 0) {
//		return usesPROC[p];
//	}
//
//	return vector<VAR>();
//}
//
//vector<ASSIGN> Uses::getUsedByASSIGN(VAR v)
//{
//	vector<ASSIGN> returnModifiesList;
//
//	//for (map<ASSIGN, vector<VAR>>::iterator it = usesASSIGN.begin(); it != usesASSIGN.end(); ++it) {
//	//	if (isUsed(it->first, v)) {
//	//		returnModifiesList.push_back(it->first);
//	//	}
//	//}
//
//	return returnModifiesList;
//}
//
//vector<STMT> Uses::getUsesBySTMT(VAR v)
//{
//	vector<STMT> returnModifiesList;
//
//	//for (map<STMT, vector<VAR>>::iterator it = usesSTMT.begin(); it != usesSTMT.end(); ++it) {
//	//	if (isUsed(it->first, v)) {
//	//		returnModifiesList.push_back(it->first);
//	//	}
//	//}
//
//	return returnModifiesList;
//}
//
//vector<PROC> Uses::getUsesByPROC(VAR v)
//{
//	vector<PROC> returnModifiesList;
//
//	//for (map<PROC, vector<VAR>>::iterator it = usesPROC.begin(); it != usesPROC.end(); ++it) {
//	//	if (isUsed(it->first, v)) {
//	//		returnModifiesList.push_back(it->first);
//	//	}
//	//}
//
//	return returnModifiesList;
//}
//
//bool Uses::isUsed(ASSIGN a, VAR v)
//{
//	if (usesASSIGN.count(a) == 0)
//	{
//		return false;
//	}
//	else
//	{
//		for (VAR var : usesASSIGN[a]) {
//			if (var == v) {
//				return true;
//			}
//		}
//
//		return false;
//	}
//}
//
//bool Uses::isUsed(STMT s, VAR v)
//{
//	if (usesSTMT.count(s) == 0)
//	{
//		return false;
//	}
//	else
//	{
//		for (VAR proc : usesSTMT[s]) {
//			if (proc == v) {
//				return true;
//			}
//		}
//
//		return false;
//	}
//}
//
//bool Uses::isUsed(PROC* p, VAR* v)
//{
//	if (usesPROC->count(p) == 0)
//	{
//		return false;
//	}
//	else
//	{
//		for (VAR* var : usesPROC[p]) {
//			if (var == v) {
//				return true;
//			}
//		}
//
//		return false;
//	}
//}
//	