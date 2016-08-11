//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef POCO_FSM_MODEL_EXPRESSION_H_
#define POCO_FSM_MODEL_EXPRESSION_H_

#include "SMC.h"

namespace Poco {
	namespace FSM {
		namespace MODEL {

			class Expression {
			public:
				Expression();
				virtual ~Expression();

				virtual const string display() const = 0;
				virtual const string token() const = 0;

				GuardPtr&			guard()				{ return _guard; }
				const GuardPtr&		guard() const 		{ return _guard; }

				OperationPtr&		operation()			{ return _operation; }
				const OperationPtr&	operation() const	{ return _operation; }

			protected:
				OperationPtr	_operation;
				mutable string	_asstring;
				GuardPtr		_guard;
				bool			_contextuel;
			};
		}
	}
}
#endif
