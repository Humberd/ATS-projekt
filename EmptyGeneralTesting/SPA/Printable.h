#pragma once
#include <string>

using namespace std;

class Printable {
protected:
	Printable();

public:
	virtual ~Printable() = 0;

	virtual string toString() const = 0;
};
