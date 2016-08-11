#pragma once

namespace Poco {
namespace FSM {
namespace MODEL {
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
enum Operator {
	NONE,
	ADD,			// +
	SUB,			// -
	MULT,			// *
	DIV,			// /
	POW,			// **
	BITXOR,			// ^
	BITAND,			// &
	BITOR,			// |
	AND,			// &&
	OR,				// ||
	NOT,			// !
	EQUAL,			// ==
	NOTEQUAL,		// !=
	LESS,			// <
	LESSOREQ,		// <=
	GREATER,		// >
	GREATEROREQ,	// >=
	SELECTOR,		// .
	ACCESSOR,		// ->
	OPENPAR,		// (
	CLOSPAR			// )
};
extern const char* const glyphes[];
extern const int precedences[];
}
}
}
