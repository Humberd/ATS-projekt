#pragma once
#include "Node.h"

/*Every node in AST has 2 numbers:
 * - sourceLineNumber
 * - programLineNumber
 * 
 * sourceLineNumber corresponds to the line in which the node is in a source file
 * 
 * programLineNumber on the other hand has a more specific meaning.
 * See the following piece of program:
 * - procedure Foo {
 * 1	if x then {
 * 2		x = 1; }
 * -
 * -	else {
 * 3		x =2; } }
 *   
 * Here I have marked a programLineNumbers.
 * Pay attention, that procedure declarations, else statements and empty lines are not counted.
 *
 * In this implementation I have decided that procedure declarations and else statements
 * will have a programLineNumber defined as -1
 */
class ProgramLineEvaluator {
public:
	explicit ProgramLineEvaluator();
	~ProgramLineEvaluator();

	void evaluate(Node* node);

	void evaluate(Node* node, int& programLineNumber);
};
