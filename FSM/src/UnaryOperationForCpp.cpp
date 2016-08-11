//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "cpp/UnaryOperationForCpp.h"

namespace Poco
{
namespace FSM
{
namespace PARSER
{
namespace CPP
{
const string UnaryOperationForCpp::display(const char* prefix) const
{
    string value;
    switch (op())
    {
    case Poco::FSM::MODEL::NOT:
        value += "!";
        break;
    default:
        value += "???";
        break;
    }
    value += dynamic_cast<ExpressionForCpp*>(operand())->display(prefix);
    return value;
}
}
}
}
}
