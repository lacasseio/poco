//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/Operation.h"

namespace Poco
{
namespace FSM
{
namespace MODEL
{

Operation::Operation(Operator op) :_operator(op)
{
}
Operation:: ~Operation()
{
}
const string Operation::token() const
{
	string result;
	switch(_operator) {
	case		NONE: result = "";break;
	case		ADD: result = "+"; break;			// +
	case		SUB: result = "-"; break;			// -
	case		MULT: result = "*"; break;			// *
	case		DIV: result = "/"; break;			// /
	case		POW: result = "**"; break;			// **
	case		BITXOR: result = "^"; break;			// ^
	case		BITAND: result = "&"; break;			// &
	case		BITOR: result = "|"; break;			// |
	case		AND: result = "&&"; break;			// &&
	case		OR: result = "||"; break;				// ||
	case		NOT: result = "!"; break;			// !
	case		EQUAL: result = "=="; break;			// ==
	case		NOTEQUAL: result = "!="; break;		// !=
	case		LESS: result = "<"; break;			// <
	case		LESSOREQ: result = "<="; break;		// <=
	case		GREATER: result = ">"; break;		// >
	case		GREATEROREQ: result = ">="; break;	// >=
	case		SELECTOR: result = "."; break;		// .
	case		ACCESSOR: result = "->"; break;		// ->
	case		OPENPAR: result = "("; break;		// (
	case		CLOSPAR: result = ")"; break;			// )
	default: result = "???";
	}
	return result;
}
//
// operator's precedence.
/*
1 	()   []   ->   .   :: 										Function call, scope, array/member access
2 	 !   ~   -   +   *   &   sizeof   type cast   ++   --   	(most) unary operators, sizeof AND type casts (right to left)
3 	*   /   % MOD 												Multiplication, division, modulo
4 	+   - 														Addition AND subtraction
5 	<<   >> 													Bitwise shift left AND right
6 	<   <=   >   >= 											Comparisons: less-than, ...
7 	==   != 													Comparisons: EQUAL AND not EQUAL
8 	& 															Bitwise	AND
9 	^ 															Bitwise exclusive OR (XOR)
10 	| 															Bitwise inclusive (normal) OR
11 	&& 															Logical AND
12 	||															Logical OR
13 	 ? : 														Conditional expression (ternary)
14 	=   +=   -=   *=   /=   %=   &=   |=   ^=   <<=   >>= 		Assignment operators (right to left)
15 	, 															Comma operator
*/
//

bool Operation::precede(const Operation* op) const
{
	const int left = precedences[this->op()];
	const int right = precedences[op->op()];
	return left >= right;
}

void Operation::setNoContextuel()
{
    if (_operator == EQUAL || _operator == NOTEQUAL || _operator == SELECTOR)
    {
        _contextuel = false;
    }
}
}
}
}