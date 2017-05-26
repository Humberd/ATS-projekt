#include "VAR.h"

VAR::VAR()
{
	this->varName = "";
}

VAR::VAR(string varName)
{
	this->varName = varName;
}

VAR::~VAR()
{
}

void VAR::setVAR(string varName)
{
	this->varName = varName;
}

string VAR::getVAR()
{
	return this->varName;
}

bool VAR::operator==(VAR & var) const
{
	return varName == var.getVAR();
}
