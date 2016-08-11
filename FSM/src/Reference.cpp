//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "model/Reference.h"
#include "model/Guard.h"
#include "model/Transition.h"

namespace Poco
{
namespace FSM
{
namespace MODEL
{
Reference::Reference(const VariablePtr variable, int lineno) : 
	Element(lineno), 
	_variable(variable)  {
}
Reference::Reference(const FunctionPtr function, int lineno) :
	Element(lineno),
	_function(function)  {
}
Reference::Reference(const LiteralPtr literal, int lineno) :
	Element(lineno),
	_literal(literal)  {
}
Reference::~Reference() {
}
bool Reference::isParameter() const
{
    GuardPtr g = guard();
    TransitionPtr transition = guard()->transition();
    if (transition->hasParameter(reference()->Element::name()))
        return true;
    else
        return false;
}
const string Reference::token() const
{
	return reference()->display();
}
const string Reference::display() const
{
	return reference()->display();
}
}
}
}
