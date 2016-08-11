//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/BinaryOperation.h"

namespace Poco
{
namespace FSM
{
namespace MODEL
{
const string BinaryOperation::display() const
{
    if (_asstring.empty())
    {
		if (!(op() == SELECTOR || op() == ACCESSOR))
			_asstring += '(';
		_asstring += _left->display();
		switch (op())
        {
		case ADD:
		case SUB:
		case MULT:
		case DIV:
		case POW:
		case EQUAL:
		case NOTEQUAL:
        case AND:
        case OR:
		case BITXOR:
			_asstring += " " + string(glyphes[op()]) + " ";
			break;
		case SELECTOR:
		case ACCESSOR:
			_asstring += string(glyphes[op()]);
			break;
		default:
            _asstring += "???";
            break;
        }
		_asstring += _right->display();
		if (!(op() == SELECTOR || op() == ACCESSOR))
			_asstring += ')';
	}
    return _asstring;
}
}
}
}