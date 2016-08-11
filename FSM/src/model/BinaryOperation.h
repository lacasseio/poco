//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef POCO_FSM_MODEL_BINARY_OPERATION_H_
#define POCO_FSM_MODEL_BINARY_OPERATION_H_

#include "Expression.h"
#include "Operation.h"

namespace Poco {
	namespace FSM {
		namespace MODEL {

			class BinaryOperation : public Operation {
			public:
				BinaryOperation(Operator op) : Operation(op, Binary), _left(NULL), _right(NULL) {
				}
				virtual ~BinaryOperation() {
				}
				ExpressionPtr&	left()				{ return _left; }
				ExpressionPtr&	right()				{ return _right; }
				const ExpressionPtr	left() const	{ return _left; }
				const ExpressionPtr	right()const	{ return _right; }
				virtual const string display() const;

			private:
				ExpressionPtr		_left;
				ExpressionPtr		_right;

			};

		}
	}
}

#endif

#if 0
conditional-expression:
    logical-OR-expression
    logical-OR-expression ? expression : conditional-expression
logical-OR-expression:
    logical-AND-expression
    logical-OR-expression   ||   logical-AND-expression
logical-AND-expression:
    inclusive-OR-expression
    logical-AND-expression   &&   inclusive-OR-expression
inclusive-OR-expression:
    exclusive-OR-expression
    inclusive-OR-expression | exclusive-OR-expression
exclusive-OR-expression:
    AND-expression
    exclusive-OR-expression ^ AND-expression
AND-expression:
    equality-expression
    AND-expression & equality-expression
equality-expression:
    relational-expression
    equality-expression == relational-expression
    equality-expression != relational-expression
relational-expression:
    shift-expression
    relational-expression < shift-expression
    relational-expression > shift-expression
    relational-expression <= shift-expression
    relational-expression => shift-expression
shift-expression:
    additive-expression
    shift-expression << additive-expression
    shift-expression >> additive-expression
additive-expression:
    multiplicative-expression
    additive-expression + multiplicative-expression
    additive-expression – multiplicative-expression
multiplicative-expression:
    segment-expression
    multiplicative-expression * segment-expression
    multiplicative-expression / segment-expression
    multiplicative-expression % segment-expression
segment-expression:
    pm-expression
    segment-expression :> pm-expression
pm-expression:
    cast-expression
    pm-expression .* cast-expression
    pm-expression –>* cast-expression
cast-expression:
    unary-expression
    ( type-name ) cast-expression 
unary-expression:
    postfix-expression
    ++ unary-expression
    –– unary-expression
    unary-operator cast-expression
    sizeof unary-expression
    sizeof ( type-name )
    allocation-expression
    deallocation-expression
unary-operator: one of
    * & + – ! ~
#endif
