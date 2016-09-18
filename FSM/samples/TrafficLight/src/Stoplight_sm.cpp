#include "stoplightdefs.h"
#include "stoplight.h"
#include "Stoplight_sm.h"
using namespace statemap;
namespace cpp_ex4 {
	// FSM Map constructor.
	StopMap::StopMap() :
		Default("Default", 0),
		EastWestGreen("EastWestGreen", 1),
		EastWestYellow("EastWestYellow", 2),
		NorthSouthGreen("NorthSouthGreen", 3),
		NorthSouthYellow("NorthSouthYellow", 4)
	{}
	
	// Class state -----------------------------------
	void StoplightState::Timeout(StoplightContext<Stoplight>& context) {
	     Default(context);
	}
	// FSM map default state class.-------------------
	void StoplightState::Default(StoplightContext<Stoplight>& context) {
	    throw TransitionUndefinedException(context.getState().getName(), context.getTransition());
	    return;
	}
	void StopMap_EastWestGreen::Entry(StoplightContext<Stoplight>& context) {
	    Stoplight& ctxt = context.getOwner();
		ctxt.setTimer(Stoplight :: EWGreenTimer );
	}
	
	// ----------------------------------------------------
	void StopMap_EastWestGreen::Timeout(StoplightContext<Stoplight>& context) {
		Stoplight& ctxt = context.getOwner();
		
		if (true) {
			context.getState().Exit(context);
			context.clearState();
			try {
				ctxt.TurnLight(EWLIGHT , YELLOW );
				context.setState(context.EastWestYellow);
			} catch (...) {
				context.setState(context.EastWestYellow);
				throw;
			}
			context.getState().Entry(context);
		} 
	}
	void StopMap_EastWestYellow::Entry(StoplightContext<Stoplight>& context) {
	    Stoplight& ctxt = context.getOwner();
		ctxt.setTimer(Stoplight :: YellowTimer );
	}
	
	// ----------------------------------------------------
	void StopMap_EastWestYellow::Timeout(StoplightContext<Stoplight>& context) {
		Stoplight& ctxt = context.getOwner();
		
		if (true) {
			context.getState().Exit(context);
			context.clearState();
			try {
				ctxt.TurnLight(EWLIGHT , RED );
				ctxt.TurnLight(NSLIGHT , GREEN );
				context.setState(context.NorthSouthGreen);
			} catch (...) {
				context.setState(context.NorthSouthGreen);
				throw;
			}
			context.getState().Entry(context);
		} 
	}
	void StopMap_NorthSouthGreen::Entry(StoplightContext<Stoplight>& context) {
	    Stoplight& ctxt = context.getOwner();
		ctxt.setTimer(Stoplight :: NSGreenTimer );
	}
	
	// ----------------------------------------------------
	void StopMap_NorthSouthGreen::Timeout(StoplightContext<Stoplight>& context) {
		Stoplight& ctxt = context.getOwner();
		
		if (true) {
			context.getState().Exit(context);
			context.clearState();
			try {
				ctxt.TurnLight(NSLIGHT , YELLOW );
				context.setState(context.NorthSouthYellow);
			} catch (...) {
				context.setState(context.NorthSouthYellow);
				throw;
			}
			context.getState().Entry(context);
		} 
	}
	void StopMap_NorthSouthYellow::Entry(StoplightContext<Stoplight>& context) {
	    Stoplight& ctxt = context.getOwner();
		ctxt.setTimer(Stoplight :: YellowTimer );
	}
	
	// ----------------------------------------------------
	void StopMap_NorthSouthYellow::Timeout(StoplightContext<Stoplight>& context) {
		Stoplight& ctxt = context.getOwner();
		
		if (true) {
			context.getState().Exit(context);
			context.clearState();
			try {
				ctxt.TurnLight(NSLIGHT , RED );
				ctxt.TurnLight(EWLIGHT , GREEN );
				context.setState(context.EastWestGreen);
			} catch (...) {
				context.setState(context.EastWestGreen);
				throw;
			}
			context.getState().Entry(context);
		} 
	}
}
