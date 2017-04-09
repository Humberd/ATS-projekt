#pragma once

class RangeNumber {
private:
	int min;
	int max;

public:
	explicit RangeNumber(int min, int max);
	~RangeNumber();

	/*Checking if a value is within range of <min,max>
	 * For example:
	 *	min=1, max=3, 
	 *	isWithinRangeInclusive(1); //true
	 *	isWithinRangeInclusive(2); //true
	 *	isWithinRangeInclusive(3); //true
	 */
	bool isWithinRangeInclusive(int value) const;

	/*Checking if a value is within range of (min,max)
	* For example:
	*	min=1, max=3,
	*	isWithinRangeExclusive(1); //false
	*	isWithinRangeExclusive(2); //true
	*	isWithinRangeExclusive(3); //false
	*/
	bool isWithinRangeExclusive(int value) const;
};