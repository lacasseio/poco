//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/Operator.h"
#include "cpp/BinaryOperationForCpp.h"

namespace Poco
{
namespace FSM
{
namespace PARSER
{
namespace CPP
{
const string BinaryOperationForCpp::display(const char* prefix) const
{
    string value;
	if (!(op() == Poco::FSM::MODEL::SELECTOR || op() == Poco::FSM::MODEL::ACCESSOR))
		value += '(';
    value += dynamic_cast<ExpressionForCpp*>(left())->display(prefix);
	switch (op())
    {
	case Poco::FSM::MODEL::ADD:
	case Poco::FSM::MODEL::SUB:
	case Poco::FSM::MODEL::MULT:
	case Poco::FSM::MODEL::DIV:
	case Poco::FSM::MODEL::POW:
	case Poco::FSM::MODEL::EQUAL:
	case Poco::FSM::MODEL::NOTEQUAL:
    case Poco::FSM::MODEL::AND:
    case Poco::FSM::MODEL::OR:
	case Poco::FSM::MODEL::BITXOR:
		value += " " + string(Poco::FSM::MODEL::glyphes[op()]) + " ";
		break;
	case Poco::FSM::MODEL::SELECTOR:
	case Poco::FSM::MODEL::ACCESSOR:
		value += string(Poco::FSM::MODEL::glyphes[op()]);
		break;
	default:
        value += "???";
        break;
    }
	if (op() == Poco::FSM::MODEL::SELECTOR || op() == Poco::FSM::MODEL::ACCESSOR) {
		ExpressionForCpp* efc = dynamic_cast<ExpressionForCpp*>(right());
		value += efc->display();
	} else {
		value += dynamic_cast<ExpressionForCpp*>(right())->display(prefix);
	}
	if (!(op() == Poco::FSM::MODEL::SELECTOR || op() == Poco::FSM::MODEL::ACCESSOR))
		value += ')';
	return value;
}

}
}
}
}
