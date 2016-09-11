//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include <iostream>
#include <algorithm>
#include "cpp/TransitionForCpp.h"
#include "cpp/ParameterForCpp.h"
#include "cpp/FSMForCpp.h"
#include "cpp/MapForCpp.h"
#include "cpp/StateForCpp.h"
#include "cpp/GuardForCpp.h"
#include "cpp/ActionForCpp.h"
#include "cpp/ExpressionForCpp.h"
#include "parser/IndentStream.h"
#include "model/Parameter.h"
#include "model/Action.h"
#include "model/Mode.h"

using Poco::FSM::MODEL::Parameter;
using Poco::FSM::MODEL::Mode;
using namespace std;

namespace Poco
{
namespace FSM
{
namespace PARSER
{
namespace CPP
{

const string TransitionForCpp::name() const
{
    string cppname = Element::name();
    replace(cppname.begin(), cppname.end(), '-', '_');
    return cppname;
}
void TransitionForCpp::generateVirtualTransitions(ostream& inc, bool debug) const
{
    if (begstate()->entry())
    {
        inc << "virtual void " << "Entry" << "(" << begstate()->map()->fsm()->context() << "& context);";
    }
    if (begstate()->exit())
    {
        inc << "virtual void " << "Exit" << "(" << begstate()->map()->fsm()->context() << "& context);";
    }
    inc << "virtual void " << name() << "(" << begstate()->map()->fsm()->context() << "& context";
    if (!_parameters.empty())
    {
        inc << ", ";
        for (int no = 0; no < _parameters.size(); ++no)
        {
            dynamic_cast<ParameterForCpp*>(_parameters[no])->generateInclude(inc, debug);
            if (no + 1 < _parameters.size())
                inc << ", ";
        }
    }
    inc << ");" << endl;
}
void TransitionForCpp::generateDefinition(ostream& inc, bool debug) const
{
    inc << "virtual void " << name() << "(" << begstate()->map()->fsm()->context() << "& context";
    if (!_parameters.empty())
    {
        inc << ", ";
        for (int no = 0; no < _parameters.size(); ++no)
        {
            dynamic_cast<ParameterForCpp*>(_parameters[no])->generateInclude(inc, debug);
            if (no + 1 < _parameters.size())
                inc << ", ";
        }
    }
    inc << ");" << endl;
}
void TransitionForCpp::generateInclude(ostream& inc, bool debug) const
{
}
void TransitionForCpp::generateCode(ostream& cpp, bool debug) const
{
	bool smcGeneration = begstate()->map()->fsm()->mode() == Mode::SMC;

    cpp << endl;
    cpp << "// ----------------------------------------------------" << endl;
    cpp << "void " << _begstate->map()->name() << '_'  << _begstate->name() << "::";
    Parameter context("context");
    context.type() = begstate()->map()->fsm()->context() + '&';
    cpp << declaration(&context) << " {"<< endl;
    cpp << tab;

    cpp << _begstate->map()->fsm()->klass() << "& ctxt = context.getOwner();" << endl;
    cpp << endl;


	List<GuardPtr>::const_iterator guard;bool oneGuardWithNullCondition = false;
	for (guard = guards().begin(); guard != guards().end(); ++guard)
    {
		poco_assert(*guard);
        if ((*guard)->condition())
        {
            ExpressionForCpp* efc = dynamic_cast<ExpressionForCpp*>((*guard)->condition());
            cpp << "if (" << efc->display("ctxt.") << ") {" << endl << tab;
		}
		else
		{
			oneGuardWithNullCondition = true;
			cpp << "if (true) {" << endl << tab;
		}
        cpp << "context.getState().Exit(context);" << endl;

		if (smcGeneration)
		{
			if ((*guard)->actions().size() > 0)
		    {
                cpp << "context.clearState();" << endl;
				cpp << "try {" << endl << tab;
            }
        }


		if (!smcGeneration)
        {
			if ((*guard)->endstate())
				cpp << "context.setState(context." << (*guard)->endstate()->name() << ");" << endl;
			
			cpp << "context.getState().Entry(context);" << endl;
			cpp << "try {" << endl << tab;
		}

		List<MODEL::ActionPtr>::const_iterator action;
		for (action = (*guard)->actions().begin(); action != (*guard)->actions().end(); ++action) {
            if (*action != NULL)
            {
                ActionForCpp* afc = static_cast<ActionForCpp*>(*action);
                cpp << "ctxt." << (*action)->display() << endl;
            }
		}
		if (!smcGeneration)
		{
			cpp << back << "} catch (...) {" << endl;
		cpp << tab << "throw;" << endl;
		cpp << back << "}" << endl;
		}

		if (smcGeneration)
		{
			if ((*guard)->endstate())
				cpp << "context.setState(context." << (*guard)->endstate()->name() << ");" << endl;

			if ((*guard)->actions().size() > 0)
			{
                cpp << back << "} catch (...) {" << endl << tab;
				if ((*guard)->endstate())
					cpp << "context.setState(context." << (*guard)->endstate()->name() << ");" << endl;
                cpp << "throw;" << endl << back;
                cpp << "}" << endl;
            }
			cpp << "context.getState().Entry(context);" << endl;
        }
		if (*guards().rbegin() == *guard && oneGuardWithNullCondition)
			cpp << back << "} " << endl;
		else
			cpp << back << "} else " << endl;
	}
	if (!oneGuardWithNullCondition)
    {
        Parameter context("context");
        MapForCpp* mfcpp = dynamic_cast<MapForCpp*>(_begstate->map());
		cpp << "if (true) {" << endl << tab;
		if (_begstate->map()->defaultState() != _begstate) {
			cpp << mfcpp->defaultStateName() << "::" << call("context") << ";" << endl;
		} else {
			cpp << "Default" << "::" << call("context") << ";" << endl;
		}
		cpp  << back << "}" << endl;
	}
	cpp << back << "}" << endl;
}
}
}
}
}
