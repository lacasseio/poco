//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef VARIABLE_FOR_CPP_H_
#define VARIABLE_FOR_CPP_H_

#include "model/Variable.h"

namespace Poco {
	namespace FSM {
		namespace PARSER {
			namespace CPP {

				class VariableForCpp : public FSM::MODEL::Variable {
				public:
					VariableForCpp(const string& name, int lineno = 0) :
						FSM::MODEL::Variable(name, lineno) {
					}
					virtual ~VariableForCpp() {
					}
					virtual const string display(const char* prefix) const;
				};

			}
		}
	}
}

#endif
