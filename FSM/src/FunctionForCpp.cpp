//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "cpp/FunctionForCpp.h"

namespace Poco
{
namespace FSM
{
namespace PARSER
{
namespace CPP
{
const string FunctionForCpp::display(const char* prefix) const
{
    if (prefix)
		return prefix + Function::display();
	else
		return  Function::display();
}
}
}
}
}
