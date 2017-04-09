#include "RangeNumber.h"

RangeNumber::RangeNumber(int min, int max) {
	this->min = min;
	this->max = max;
}

RangeNumber::~RangeNumber() {
}

bool RangeNumber::isWithinRangeInclusive(int value) const {
	return value >= min && value <= max;
}

bool RangeNumber::isWithinRangeExclusive(int value) const {
	return value > min && value < max;
}
