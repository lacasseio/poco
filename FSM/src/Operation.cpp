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

bool Operation::precede(const Operation& op) const
{
	return true;
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