#pragma once
#include <exception>
#include <string>

using namespace std;

class ValidateException : public exception
{
public:
	explicit ValidateException(const string& _Message);

	explicit ValidateException(const char *_Message);

};

