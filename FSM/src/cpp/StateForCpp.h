//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef  POCO_FSM_CPP_STATE_H_
#define  POCO_FSM_CPP_STATE_H_

#include "model/State.h"
#include "CompilableForCpp.h"

namespace Poco {
	namespace FSM {
		namespace PARSER {
			namespace CPP {

				class StateForCpp : public CompilableForCpp, public FSM::MODEL::State {
				public:
					StateForCpp(const string& name, int lineno = 0) :
						FSM::MODEL::State(name, lineno) {
					}
					virtual ~StateForCpp() {
					}
					virtual void generateInclude(ostream& inc,bool debug = false) const;
					virtual void generateCode(ostream& cpp, bool debug = false) const;

					void generateForwarDeclaration(ostream& inc, bool debug = false) const;
					void generateVirtualTransitions(ostream& inc, bool debug = false) const;
					void generateDefinition(ostream& inc, bool debug = false) const;
					void generateDeclaration(ostream& cpp, int no) const;
					
				private:
					string statename() const;

				};

			}
		}
	}
}
#endif
