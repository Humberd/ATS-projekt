#include "PROC.h"

PROC::PROC()
{
	this->procName = "";
}

PROC::PROC(string procName)
{
	this->procName = procName;
}

PROC::~PROC()
{
}

void PROC::setProc(string procName)
{
	this->procName = procName;
}

string PROC::getProc()
{
	return this->procName;
}

bool PROC::operator==(PROC &proc) const
{
	return procName == proc.getProc();
}
