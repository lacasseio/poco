//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef UNARYOPERATIONFORCPP_H_
#define UNARYOPERATIONFORCPP_H_

#include "model/UnaryOperation.h"
#include "ExpressionForCpp.h"

namespace Poco {
	namespace FSM {
		namespace PARSER {
			namespace CPP {

				class UnaryOperationForCpp : public ExpressionForCpp, public FSM::MODEL::UnaryOperation {
				public:
					UnaryOperationForCpp(Poco::FSM::MODEL::Operator op) :
						FSM::MODEL::UnaryOperation(op) {
					}
					virtual ~UnaryOperationForCpp() {
					}
					virtual const string display(const char* prefix = NULL) const;
				};

			}
		}
	}
}

#endif
