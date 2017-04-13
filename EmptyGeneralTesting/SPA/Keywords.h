#pragma once
#include <string>

using namespace std;

class Keywords {
private:
	Keywords();
	~Keywords();
public:
	static const string PROCEDURE;
	static const string WHILE;
	static const string IF;
	static const string THEN;
	static const string ELSE;
	static const string CALL;
};
