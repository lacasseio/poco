//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef POCO_FSM_MODEL_OPERATION_H_
#define POCO_FSM_MODEL_OPERATION_H_

#include "model/Expression.h"
#include "model/Operator.h"

namespace Poco {
	namespace FSM {
		namespace MODEL {
			enum Arity {
				Zeroary,
				Unary,
				Binary,
				Ternary
			};
			class Operation : public virtual Expression {
			public:
				Operation(Operator op);
				virtual ~Operation();

				virtual const string token() const;
				bool precede(const Operation& op) const;

				const bool&	contextuel() const		{ return _contextuel; }
				const Operator&		op() const		{ return _operator; }
				const Arity&		arity() const	{ return _arity; }

				void setNoContextuel();

			protected:
				Operation(Operator ope, Arity arity) : _contextuel(true), _operator(ope), _arity(arity) {}

			private:
				bool			_contextuel;
				Operator		_operator;
				Arity			_arity;
			};
		}
	}
}
#endif
