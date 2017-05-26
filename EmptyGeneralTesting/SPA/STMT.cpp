#include "STMT.h"

STMT::STMT()
{
	this->stmt = 0;
}

STMT::STMT(int stmt)
{
	this->stmt = stmt;
}

STMT::~STMT()
{
}

void STMT::setSTMT(int stmt)
{
	this->stmt = stmt;
}

int STMT::getSTMT()
{
	return this->stmt;
}

bool STMT::operator==(STMT & rstmt) const
{
	return stmt == rstmt.getSTMT();
}
