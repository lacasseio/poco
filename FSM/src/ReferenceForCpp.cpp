//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "cpp/ReferenceForCpp.h"
#include "cpp/VariableForCpp.h"
#include "cpp/LiteralForCpp.h"
#include "cpp/FunctionForCpp.h"

using namespace Poco::FSM::MODEL;

namespace Poco
{
namespace FSM
{
namespace PARSER
{
namespace CPP
{
void ReferenceForCpp::generateInclude(ostream& inc, bool debug) const
{
}
void ReferenceForCpp::generateCode(ostream& cpp, bool debug) const
{
}
const string ReferenceForCpp::display(const char* prefix) const
{
	LiteralForCpp* lfc;
	VariableForCpp* vfc;
	FunctionForCpp* ffc;
	
	lfc = dynamic_cast<LiteralForCpp*>(reference());
	vfc = dynamic_cast<VariableForCpp*>(reference());
	ffc = dynamic_cast<FunctionForCpp*>(reference());

	if (isParameter()) {
		if (vfc)
			return vfc->Variable::display();
		else
		if (ffc)
			return ffc->Function::display();
		else
		if (lfc)
			return lfc->Literal::display();
		else
			poco_assert(false);
    }
    else
    {
		if (vfc)
			return vfc->display(prefix);
		else if (ffc)
			return ffc->display(prefix);
		else if (lfc)
			return lfc->Literal::display();
		else
			poco_assert(false);
    }
}
}
}
}
}
