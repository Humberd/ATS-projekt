#include "ASSIGN.h"

ASSIGN::ASSIGN()
{
	this->assign = 0;
}

ASSIGN::ASSIGN(int assign)
{
	this->assign = assign;
}

ASSIGN::~ASSIGN()
{
}

void ASSIGN::setASSIGN(int assign)
{
	this->assign = assign;
}

int ASSIGN::getASSIGN()
{
	return this->assign;
}

bool ASSIGN::operator==(ASSIGN &rassign) const
{
	return assign == rassign.getASSIGN();
}