//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/UnaryOperation.h"

namespace Poco
{
namespace FSM
{
namespace MODEL
{
const string UnaryOperation::display() const
{
    if (_asstring.empty())
    {
        switch (op())
        {
        case NOT:
            _asstring += '!';
			break;
        }
        if (_operand)
			_asstring += _operand->display();
    }
    return _asstring;
}
}
}
}