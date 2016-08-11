//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <typeinfo>

#include "Poco/Bugcheck.h"
#include "Poco/NumberFormatter.h"
#include "Poco/StreamTokenizer.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Ascii.h"
#include "Poco/String.h"

using Poco::Bugcheck;
using Poco::NumberFormatter;
using Poco::StreamTokenizer;
using Poco::SyntaxException;
using Poco::InvalidToken;
using Poco::EOFToken;
using Poco::WhitespaceToken;
using Poco::Path;
using Poco::File;
using Poco::Ascii;

#include "parser/Parser.h"
#include "parser/Identifier.h"
#include "parser/Number.h"
#include "parser/Keyword.h"
#include "parser/Comment.h"
#include "parser/Character.h"
#include "parser/Glyphe.h"
#include "parser/String.h"

#include "model/Action.h"
#include "model/FSM.h"
#include "model/Guard.h"
#include "model/Map.h"
#include "model/Parameter.h"
#include "model/State.h"
#include "model/Entry.h"
#include "model/Exit.h"
#include "model/Transition.h"
#include "model/Expression.h"
#include "model/Transition.h"
#include "model/Reference.h"
#include "model/Variable.h"
#include "model/Function.h"
#include "model/Literal.h"
#include "model/Reference.h"
#include "model/Argument.h"
#include "model/Operation.h"
#include "model/UnaryOperation.h"
#include "model/BinaryOperation.h"

#include "model/Factory.h"
#include "cpp/FactoryForCpp.h"

using namespace std;

using Poco::FSM::MODEL::Action;
using Poco::FSM::MODEL::FSM;
using Poco::FSM::MODEL::Guard;
using Poco::FSM::MODEL::Map;
using Poco::FSM::MODEL::Parameter;
using Poco::FSM::MODEL::State;
using Poco::FSM::MODEL::Transition;
using Poco::FSM::MODEL::ActionPtr;
using Poco::FSM::MODEL::FSMPtr;
using Poco::FSM::MODEL::GuardPtr;
using Poco::FSM::MODEL::MapPtr;
using Poco::FSM::MODEL::ParameterPtr;
using Poco::FSM::MODEL::StatePtr;
using Poco::FSM::MODEL::TransitionPtr;
using Poco::FSM::MODEL::FunctionPtr;
using Poco::FSM::MODEL::VariablePtr;
using Poco::FSM::MODEL::LiteralPtr;
using Poco::FSM::MODEL::ExpressionPtr;
using Poco::FSM::MODEL::ArgumentPtr;
using Poco::FSM::MODEL::Arity;
using Poco::FSM::MODEL::Operation;
using Poco::FSM::MODEL::UnaryOperation;
using Poco::FSM::MODEL::BinaryOperation;

static const char TAB = '\t';

static const Poco::FSM::MODEL::Factory& factory = Poco::FSM::PARSER::CPP::FactoryForCpp();

namespace Poco
{
namespace FSM
{
namespace PARSER
{

Parser::Parser(Logger& logger, const File& file, istream& istr) :
    _logger(logger),
    _istr(istr),
    _tokenizer(_istr),
    _file(file),
	fsm (NULL),
	state(NULL),
	guard(NULL),
	map(NULL),
	action(NULL),
	transition(NULL),
	parameter(NULL),
	entry (NULL),
	exit (NULL)
{
}
Parser:: ~Parser()
{
}

FSMPtr Parser::parse(const Path& out)
{
    try
    {
        fsm = factory.newFSM(this);
        const Token* next = nextToken();
        next = parseFile(next, out);
        if (next && !isEOF(next))
            syntaxError("Additional tokens behind supposed EOF");
    }
    catch (SyntaxException& exc)
    {
        string m(exc.message());
        string where(_currentPath);
        where.append("(");
        where.append(NumberFormatter::format(_istr.getCurrentLineNumber()));
        where.append(")");
        throw SyntaxException(m, where);
    }
    return fsm;
}
inline bool Parser::isString(const Token* token)
{
    return token->is(Token::STRING_LITERAL_TOKEN);
}
inline bool Parser::isCharacter(const Token* token)
{
    return token->is(Token::CHAR_LITERAL_TOKEN);
}
inline bool Parser::isNumber(const Token* token)
{
    return token->is(Token::INTEGER_LITERAL_TOKEN) || token->is(Token::LONG_INTEGER_LITERAL_TOKEN);
}

inline bool Parser::isIdentifier(const Token* token)
{
    return token->is(Token::IDENTIFIER_TOKEN) || isOperator(token, Glyphe::DBL_COLON);
}


inline bool Parser::isOperator(const Token* token)
{
    return token->is(Token::OPERATOR_TOKEN);
}

inline bool Parser::isOperator(const Token* token, int kind)
{
    return token->is(Token::OPERATOR_TOKEN) && token->asInteger() == kind;
}


inline bool Parser::isKeyword(const Token* token, int kind)
{
    return token->is(Token::KEYWORD_TOKEN) && token->asInteger() == kind;
}


inline bool Parser::isEOF(const Token* token)
{
    return token->is(Token::EOF_TOKEN);
}
const char* classToString(Token::Class klass)
{
    switch (klass)
    {
    case Token::IDENTIFIER_TOKEN:
        return "IDENTIFIER";
    case Token::KEYWORD_TOKEN:
        return "KEYWORD";
    case Token::SEPARATOR_TOKEN:
        return "SEPARATOR";
    case Token::OPERATOR_TOKEN:
        return "OPERATOR";
    case Token::STRING_LITERAL_TOKEN:
        return "STRING_LITERAL";
    case Token::CHAR_LITERAL_TOKEN:
        return "CHAR_LITERAL";
    case Token::INTEGER_LITERAL_TOKEN:
        return "INTEGER_LITERAL";
    case Token::LONG_INTEGER_LITERAL_TOKEN:
        return "LONG_INTEGER_LITERAL";
    case Token::FLOAT_LITERAL_TOKEN:
        return "FLOAT_LITERAL";
    case Token::DOUBLE_LITERAL_TOKEN:
        return "DOUBLE_LITERAL";
    case Token::COMMENT_TOKEN:
        return "COMMENT";
    case Token::SPECIAL_COMMENT_TOKEN:
        return "SPECIAL_COMMENT";
    case Token::PREPROCESSOR_TOKEN:
        return "PREPROCESOR";
    case Token::WHITESPACE_TOKEN:
        return "WHITESPACE";
    case Token::EOF_TOKEN:
        return "EOF";
    case Token::INVALID_TOKEN:
        return "INVALID";
    case Token::USER_TOKEN:
        return "USER";
    }
    return "???";
}

const Token* Parser::parseFile(const Token* next, const Path& out)
{
    while (next->is(Token::KEYWORD_TOKEN) || next->is(Token::OPERATOR_TOKEN))
    {
        if (next->is(Token::KEYWORD_TOKEN))
            switch (next->asInteger())
            {
            case Keyword::START:	// %start
                next = parseStart(next);
                break;
            case Keyword::CLASS: 	// %class
                next = parseClass(next);
                break;
            case Keyword::FSMFILE: 	// %fsmfile
                next = parseFSMFile(next);
                break;
            case Keyword::FSMCLASS: 	// %fsmclass
                next = parseFSMClass(next);
                break;
            case Keyword::HEADER:	// %header
                next = parseHeader(next);
                break;
            case Keyword::INCLUDE: 	// %include
                next = parseIncludes(next);
                break;
            case Keyword::PACKAGE: 	// %package
                next = parsePackage(next);
                break;
            case Keyword::IMPORT: 	// %import
                next = parseImport(next);
                break;
            case Keyword::DECLARE: 	// %declare
                next = parseDeclare(next);
                break;
            case Keyword::ACCESS: 	// %access
                next = parseAccess(next);
                break;
            case Keyword::MAP:		// %map
				if (fsm->fsmclass().empty())
					fsm->fsmclass() = fsm->klass() + "Context";
				if (fsm->fsmfile().empty())
					fsm->fsmfile() = fsm->klass() + "_sm";
                fsm->setcontext();

                if (fsm->updated(out))
                {
                    fsm->updated() = true;
                    return NULL;
                }

                next = parseMap(next);
                break;
            case Keyword::RETURN: 	// %return
                next = parseReturn(next);
                break;
            default:
                poco_bugcheck();
                break;
            }
        else if (next->is(Token::OPERATOR_TOKEN))
            switch (next->asInteger())
            {
            case Glyphe::OPENCODE:	// %{
                next = parseRawCode(next);
                break;
            default:
                poco_bugcheck();
            }
    }
    return next;
}
const Token* Parser::parseSource(const Token* next)
{
    return next;
}
const Token* Parser::parseReturn(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::RETURN));
    const string rcclass = next->tokenString();
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string klass = next->tokenString();
        fsm->returnt() = klass;
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseStart(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::START));
    const string keyword = next->tokenString();

    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string startstate = next->tokenString();
        next = nextToken();
        if (isOperator(next, Glyphe::DBL_COLON))
        {
            startstate += next->tokenString();
            next = nextToken();
            if (next->is(Token::IDENTIFIER_TOKEN))
            {
                startstate += next->tokenString();
                next = nextToken();
            }
        }
        fsm->startState() = startstate;

    }
    return next;
}
const Token* Parser::parseClass(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::CLASS));
    const string pcclass = next->tokenString();
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string klass = next->tokenString();
        fsm->klass() = klass;
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseFSMFile(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::FSMFILE));
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string fsmfile = next->tokenString();
        fsm->fsmfile() = fsmfile;
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseFSMClass(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::FSMCLASS));
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string fsmclass = next->tokenString();
        fsm->fsmclass() = fsmclass;
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseHeader(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::HEADER));
    const string pcheader = next->tokenString();
    next = nextToken();
    string file;
    do
    {
        file += next->tokenString();
        next = nextToken();
    }
    while (!next->is(Token::KEYWORD_TOKEN));
    fsm->header() = file;
    return next;
}
const Token* Parser::parseIncludes(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::INCLUDE));
    next = nextToken();
    for (;;)
    {
        next = parseInclude(next);
        if (isOperator(next, Glyphe::COMMA))
            next = nextToken();
        else
            break;
    }
    return next;
}
const Token* Parser::parseInclude(const Token* next)
{
    if (next->is(Token::STRING_LITERAL_TOKEN))
    {
        string file = next->tokenString().substr(1); // remove begin "
        file = file.substr(0, file.size() - 1);		 // remove ending "
        fsm->includes().push_back(file);
        next = nextToken();
    }
    else if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string file = next->tokenString();
        next = nextToken();
        if (isOperator(next, Glyphe::PERIOD))
        {
            file += '.';
            next = nextToken();
            if (next->is(Token::IDENTIFIER_TOKEN))
            {
                file += next->tokenString();
                fsm->includes().push_back(file);
                next = nextToken();
            }
        }
    }
    return next;
}
const Token* Parser::parsePackage(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::PACKAGE));
    const string pcpackage = next->tokenString();
    next = nextToken();
    string packages;
    do
    {
        if (next->is(Token::IDENTIFIER_TOKEN))
        {
            string package = next->tokenString();
            fsm->addPackage(package);
            packages += package;
            next = nextToken();
            if (isOperator(next, Glyphe::DBL_COLON))
            {
                packages += next->tokenString();
                next = nextToken();
            }
        }
    }
    while (!next->is(Token::KEYWORD_TOKEN));
    return next;
}
const Token* Parser::parseImport(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::IMPORT));
    const string pcimport = next->tokenString();
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string import = next->tokenString();
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseDeclare(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::DECLARE));
    const string pcdeclare = next->tokenString();
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string declare = next->tokenString();
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseAccess(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::ACCESS));
    const Token* token = next;
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        string access = next->tokenString();
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseMap(const Token* next)
{
    poco_assert(isKeyword(next, Keyword::MAP));
    next = nextToken();
    if (next->is(Token::IDENTIFIER_TOKEN))
    {
        map = factory.newMap(next->tokenString());
        fsm->add(map);
        next = nextToken();
        next = parseStates(next);
        if (map->defaultState() == NULL)
            map->defaultState() = factory.newState("Default");
    }
    return next;
}
const Token* Parser::parseStates(const Token* next)
{
    poco_assert(isOperator(next, Glyphe::FSM));
    const Token* token = next;
// OPEN { 	// Transport connection is open
// 		WAIT										CLOSING				{}
// 		TDISreq(tsdu: TPDU::DR&)	[P7()]			CLOSING				{DR(tsdu);}
// }
    next = nextToken();
    do
    {
        next = parseState(next);
    }
    while (!isOperator(next, Glyphe::FSM));
    next = nextToken();
    return next;
}
const Token* Parser::parseState(const Token* next)
{
    poco_assert(isIdentifier(next));
    state = map->lookfor(next->tokenString());
    if (state == NULL)
    {
        state = factory.newState(next->tokenString());
        map->add(state);
    }
    map->add(state);
    next = nextToken();
    next = parseEntry(next);
    state->entry() = entry;
    next = parseExit(next);
    state->exit() = exit;
    next = parseTransitions(next);
    next = nextToken();
    return next;
}
const Token* Parser::parseEntry(const Token* next)
{
    entry = NULL;
    if (isOperator(next, Glyphe::OPENBRACE))
        return next;
    poco_assert(next->tokenString() == "Entry");
    entry = factory.newEntry("Entry");
    next = nextToken();
    next = parseActions(next, entry->actions());
    return next;
}
const Token* Parser::parseExit(const Token* next)
{
	exit = NULL;
	if (isOperator(next, Glyphe::OPENBRACE))
        return next;
    poco_assert(next->tokenString() == "Exit");
    exit = factory.newExit("Exit");
    next = nextToken();
    next = parseActions(next, exit->actions());
    return next;
}
const Token* Parser::parseTransitions(const Token* next)
{
    poco_assert(isOperator(next, Glyphe::OPENBRACE));
    next = nextToken();
    while (!isOperator(next, Glyphe::CLOSBRACE))
    {
        next = parseTransition(next);
    }
    return next;
}
const Token* Parser::parseTransition(const Token* next)
{
    poco_assert(isIdentifier(next));
    string name = next->tokenString();
    next = nextToken();
    next = parseParameters(next);
    transition = state->get(name, parameters);
    if (transition == NULL)
    {
        transition = factory.newTransition(name);
		List<ParameterPtr>::const_iterator parameter;

        for (parameter = parameters.begin(); parameter != parameters.end(); ++parameter)
            if (*parameter != NULL)
                transition->add(*parameter);
        state->add(transition);
        map->add(transition);
    }
    guard = NULL;
    next = parseGuard(next);
    transition->add(guard);
    next = parseNext(next);
    next = parseActions(next, guard->actions());
//	_dump(transition, guard);
    return next;
}
const Token* Parser::parseTransitionArgs(const Token* next)
{
    next = nextToken();
    return next;
}
const Token* Parser::parseGuard(const Token* next)
{
    guard = factory.newGuard("");
    if (isOperator(next, Glyphe::OPENBRACKET))
    {
        do
        {
            next = nextToken();
            next = parseExpression(next, guard->condition());
        }
        while (!isOperator(next, Glyphe::CLOSBRACKET));
        guard->condition()->guard() = guard;
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseTerminal(const Token* next, ReferencePtr& reference)
{
    poco_assert(isIdentifier(next) || isNumber(next) || isString(next));
	if (isIdentifier(next))
	{
		const Token* identifier = next; // true/false not supported
		next = nextToken();
		if (isOperator(next, Glyphe::OPENPARENT))
		{
		    FunctionPtr function = factory.newFunction(identifier->tokenString());
		    next = parseArguments(next, function->arguments());
		    reference = factory.newReference(function);
		}
		else
		{
			VariablePtr variable = factory.newVariable(identifier->tokenString());
			reference = factory.newReference(variable);
		}
		reference->guard() = guard;
	} else {
		LiteralPtr literal = factory.newLiteral(next->tokenString());
		reference = factory.newReference(literal);
	}
    return next;
}

bool precede(const ExpressionPtr left, const ExpressionPtr right)
{
	//
	// operator's precedence.
	/*
	1 	()   []   ->   .   :: 										Function call, scope, array/member access
	2 	 !   ~   -   +   *   &   sizeof   type cast   ++   --   	(most) unary operators, sizeof AND type casts (right to left)
	3 	*   /   % MOD 												Multiplication, division, modulo
	4 	+   - 														Addition AND subtraction
	5 	<<   >> 													Bitwise shift left AND right
	6 	<   <=   >   >= 											Comparisons: less-than, ...
	7 	==   != 													Comparisons: EQUAL AND not EQUAL
	8 	& 															Bitwise	AND
	9 	^ 															Bitwise exclusive OR (XOR)
	10 	| 															Bitwise inclusive (normal) OR
	11 	&& 															Logical AND
	12 	||															Logical OR
	13 	 ? : 														Conditional expression (ternary)
	14 	=   +=   -=   *=   /=   %=   &=   |=   ^=   <<=   >>= 		Assignment operators (right to left)
	15 	, 															Comma operator
	*/
	//
	return true;
}
bool Parser::isOperator(ExpressionPtr expression, Operator op)
{
	const Operation* ope = dynamic_cast<const Operation*>(expression);
	if (ope)
		return ope->op() == op;
	return false;
}
const Token* Parser::parseExpression(const Token* next, ExpressionPtr& expression)
{
    poco_assert(isIdentifier(next) || isNumber(next) || isOperator(next, Glyphe::NOT) || isOperator(next, Glyphe::OPENPARENT));
	List<ExpressionPtr> postfix;
	Stack<ExpressionPtr> stack;

/*
P Postfix order list, Q Infix order list
Start with an empty stack.  We scan Q from left to right. 

While (we have not reached the end of Q)
    If (an operand is found)
        Add it to P
    End-If
    If (a left parenthesis is found) 
        Push it onto the stack
    End-If
    If (a right parenthesis is found) 
        While (the stack is not empty AND the top item is not a left parenthesis)
            Pop the stack and add the popped value to P
        End-While
        Pop the left parenthesis from the stack and discard it 
    End-If
    If (an operator is found)
        If (the stack is empty or if the top element is a left parenthesis)
            Push the operator onto the stack
        Else  
            While (the stack is not empty AND the top of the stack 
                    is not a left parenthesis AND precedence of the                  
                    operator <= precedence of the top of the stack)
                Pop the stack and add the top value to P
            End-While
            Push the latest operator onto the stack     
        End-If  
    End-If
End-While
While (the stack is not empty)
    Pop the stack and add the popped value to P
*/
	for(;;) {
		if (isOperator(next, Glyphe::SEMICOLON) || isOperator(next, Glyphe::CLOSBRACKET))
			break;

		if (isIdentifier(next) || isNumber(next) || isString(next) ) {
			ReferencePtr reference;
			next = parseTerminal(next, reference);
			postfix.push_back(reference); 
		} else
		if (isOperator(next, Glyphe::OPENPARENT)) {
			Operation* op = factory.newUnaryOperation(FSM::MODEL::OPENPAR);
			stack.push(op);  
			next = nextToken();
		} else
		if (isOperator(next, Glyphe::CLOSPARENT)) {
			while(stack.size() && !isOperator(stack.top(), FSM::MODEL::OPENPAR)) {
				postfix.push_back(stack.top());stack.pop();
			}
			stack.pop();
			next = nextToken();
		} else
		if (isOperator(next)) {
			Operation* ope = nullptr;
			switch (next->asInteger())
			{
			case Glyphe::NE:
				ope = factory.newBinaryOperation(FSM::MODEL::NOTEQUAL);
				break;
			case Glyphe::EQ:
				ope = factory.newBinaryOperation(FSM::MODEL::EQUAL);
				break;
			case Glyphe::AND:
				ope = factory.newBinaryOperation(FSM::MODEL::AND);
				break;
			case Glyphe::PLUS:
				ope = factory.newBinaryOperation(FSM::MODEL::ADD);
				break;
			case Glyphe::MINUS:
				ope = factory.newBinaryOperation(FSM::MODEL::SUB);
				break;
			case Glyphe::STAR:
				ope = factory.newBinaryOperation(FSM::MODEL::MULT);
				break;
			case Glyphe::SLASH:
				ope = factory.newBinaryOperation(FSM::MODEL::DIV);
				break;
			case Glyphe::STARSTAR:
				ope = factory.newBinaryOperation(FSM::MODEL::POW);
				break;
			case Glyphe::OR:
				ope = factory.newBinaryOperation(FSM::MODEL::OR);
				break;
			case Glyphe::XOR:
				ope = factory.newBinaryOperation(FSM::MODEL::BITXOR);
				break;
			case Glyphe::ARROW:
				ope = factory.newBinaryOperation(FSM::MODEL::ACCESSOR);
				break;
			case Glyphe::PERIOD:
				ope = factory.newBinaryOperation(FSM::MODEL::SELECTOR);
				break;
			case Glyphe::NOT:
				ope = factory.newUnaryOperation(FSM::MODEL::NOT);
				break;
			case Glyphe::OPENPARENT:
				ope = factory.newUnaryOperation(FSM::MODEL::OPENPAR);
				break;
			case Glyphe::CLOSPARENT:
				ope = factory.newUnaryOperation(FSM::MODEL::CLOSPAR);
				break;
			default:
				poco_assert(false);
				break;
			}
			if (stack.empty() || isOperator(stack.top(), FSM::MODEL::OPENPAR))
				stack.push(ope);
			else {
				while(stack.size() && !isOperator(stack.top(), FSM::MODEL::OPENPAR) && precede(ope, stack.top())) {
					postfix.push_back(stack.top());stack.pop();
				}
				stack.push(ope);
			}
			next = nextToken();
		}
	}
	while(stack.size()) {
		postfix.push_back(stack.top()); stack.pop();
	}


/*
Start with an empty stack.  We scan P from left to right.

While (we have not reached the end of P)
	If an operand is found
		push it onto the stack
	End-If
	If an operator is found
		Pop the stack and call the value A
		Pop the stack and call the value B
		Evaluate B op A using the operator just found.
		Push the resulting value onto the stack
	End-If
End-While
Pop the stack (this is the final value)
*/
	List<ExpressionPtr>::const_iterator ci;
	for(ci = postfix.begin(); ci != postfix.end(); ++ci) {
		ReferencePtr operand = dynamic_cast<ReferencePtr>(*ci);
		OperationPtr operation = dynamic_cast<OperationPtr>(*ci);
		if (operand) {
			stack.push(operand);
		}
		if (operation) {
			if (operation->arity() == Arity::Unary) {
				UnaryOperation* monop = static_cast<UnaryOperation*>(operation);
				monop->operand() = stack.top();stack.pop();
				stack.push(monop);
			} else
			if (operation->arity() == Arity::Binary) {
				BinaryOperation* binop = static_cast<BinaryOperation*>(operation);
				binop->right() = stack.top();stack.pop();
				binop->left() = stack.top();stack.pop();
				stack.push(binop);
			}
		}
	}
	poco_assert(stack.size() == 1);
	expression = stack.top();
	stack.pop();
    return next;
}
const Token* Parser::parseNext(const Token* next)
{
    poco_assert(isIdentifier(next));

    StatePtr endstate = map->lookfor(next->tokenString());
    if (endstate == NULL && next->tokenString() != "nil")
    {
        endstate = factory.newState(next->tokenString());
        map->add(endstate);
    }
    guard->endstate() = endstate;
    next = nextToken();
    return next;
}
const Token* Parser::parseParameters(const Token* next)
{
    parameters.clear();
    if (isOperator(next, Glyphe::OPENPARENT))
    {
        do
        {
            next = nextToken();
            next = parseParameter(next);
            parameters.push_back(parameter);
        }
        while (!isOperator(next, Glyphe::CLOSPARENT));
        next = nextToken();
    }
    return next;
}
const Token* Parser::parseParameter(const Token* next)
{
    poco_assert(isIdentifier(next));
    parameter = factory.newParameter(next->tokenString());
    do
    {
        next = nextToken();
        poco_assert(isOperator(next, Glyphe::COLON));
        string type;
        for (;;)
        {
            next = nextToken();
            if (isOperator(next, Glyphe::CLOSPARENT) || isOperator(next, Glyphe::COMMA))
                break;
            string token = next->tokenString();
            if (token == "const" || token == "unsigned" || token == "long")
                token += ' ';
            type += token;
        }
        parameter->type()= type;
    }
    while (!(isOperator(next, Glyphe::CLOSPARENT) || isOperator(next, Glyphe::COMMA)));
    return next;
}
const Token* Parser::parsePushTransition(const Token* next)
{
    next = nextToken();
    return next;
}
const Token* Parser::parsePopTransition(const Token* next)
{
    next = nextToken();
    return next;
}
const Token* Parser::parsePopArguments(const Token* next)
{
    next = nextToken();
    return next;
}
const Token* Parser::parseActions(const Token* next, List<ActionPtr>& actions)
{
    poco_assert(isOperator(next, Glyphe::OPENBRACE));
    const Token* token = next;
    next = nextToken();
    for (;;)
    {
        if (isOperator(next, Glyphe::CLOSBRACE))
            break;
        action = NULL;
        next = parseAction(next);
        actions.push_back(action);
    }
    next = nextToken();
    return next;
}
const Token* Parser::parseAction(const Token* next)
{
    poco_assert(isIdentifier(next));
    action = factory.newAction(next->tokenString());
    next = nextToken();
    next = parseArguments(next, action->arguments());
    poco_assert(isOperator(next, Glyphe::SEMICOLON));
    next = nextToken();
    return next;
}
const Token* Parser::parseArguments(const Token* next, List<ArgumentPtr>& arguments)
{
    poco_assert(isOperator(next, Glyphe::OPENPARENT));
    next = nextToken();
    for (;;)
    {
        if (isOperator(next, Glyphe::CLOSPARENT))
            break;
        if (isOperator(next, Glyphe::COMMA))
            next = nextToken();
        next = parseArgument(next, arguments);
    }
    poco_assert(isOperator(next, Glyphe::CLOSPARENT));
    next = nextToken();
    return next;
}
const Token* Parser::parseArgument(const Token* next, List<ArgumentPtr>& arguments)
{
	string msg = next->asString() + ':';
	poco_assert_msg(isIdentifier(next) || isNumber(next) || isString(next) || isCharacter(next) ||
					 isOperator(next, Glyphe::STAR) || isOperator(next, Glyphe::BITAND), msg.c_str());
    string code;
    int count = 0;
    for (;;)
    {
        if (isOperator(next, Glyphe::COMMA))
            break;
        if (isOperator(next, Glyphe::CLOSPARENT) && count-- == 0)
        {
            break;
        }
        if (isOperator(next, Glyphe::OPENPARENT))
            count += 1;
		code += next->tokenString();
		code += ' ';
		next = nextToken();
    }
    ArgumentPtr argument = factory.newArgument(code);
    arguments.push_back(argument);
    return next;
}
const Token* Parser::parseRawCode(const Token* next)
{
    do
    {
        next = nextToken();
    }
    while (!isOperator(next, Glyphe::CLOSCODE));
    next = nextToken();
    return next;
}
const Token* Parser::nextToken()
{
    return nextParserToken();
}

const Token* Parser::nextParserToken()
{
    const Poco::Token* next = _tokenizer.nextToken();
    while (next->is(Token::COMMENT_TOKEN) || next->is(Token::SPECIAL_COMMENT_TOKEN))
    {
        next = _tokenizer.nextToken();
    }
    return static_cast<const Token*>(next);;
}
void Parser::syntaxError(const string& msg)
{
    throw SyntaxException("Expected", msg);
}
}
}
}
