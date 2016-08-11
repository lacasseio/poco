//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/Operator.h"

namespace Poco
{
namespace FSM
{
namespace MODEL
{

const char* const glyphes[] = {
	"",		//	NONE
	"+",	//	ADD,			// +
	"-",	//	SUB,			// -
	"*",	 //	MULT,			// *
	"/",	 //	DIV,			// /
	"**",	//	POW,			// **
	"^",	//	BITXOR,			// ^
	"&",	//	BITAND,			// &
	"|",	 //	BITOR,			// |
	"&&",	//	AND,			// &&
	"||",	//	OR,				// ||
	"!",	//	NOT,			// !
	"==",	//	EQUAL,			// ==
	"!=",	//	NOTEQUAL,		// !=
	"<",	//	LESS,			// <
	"<=",	//	LESSOREQ,		// <=
	">",	//	GREATER,		// >
	">=",	//	GREATEROREQ,	// >=
	".",	//	SELECTOR,		// .
	"->",	//	ACCESSOR,		// ->
	"(",	//	OPENPAR,		// (
	")",	//	CLOSPAR			// )
};
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
const int const precedences[] = {
	0,	//	NONE
	4,	//	ADD,			// +
	4,	//	SUB,			// -
	3,	//	MULT,			// *
	3,	//	DIV,			// /
	3,	//	POW,			// **
	9,	//	BITXOR,			// ^
	8,	//	BITAND,			// &
	10,	//	BITOR,			// |
	11,	//	AND,			// &&
	12,	//	OR,				// ||
	2,	//	NOT,			// !
	7,	//	EQUAL,			// ==
	7,	//	NOTEQUAL,		// !=
	6,	//	LESS,			// <
	6,	//	LESSOREQ,		// <=
	6,	//	GREATER,		// >
	6,	//	GREATEROREQ,	// >=
	1,	//	SELECTOR,		// .
	1,	//	ACCESSOR,		// ->
	1,	//	OPENPAR,		// (
	1,	//	CLOSPAR			// )
};
}
}
}