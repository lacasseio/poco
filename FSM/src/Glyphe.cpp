//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include "Poco/Ascii.h"

#include "Poco/StreamTokenizer.h"
using Poco::StreamTokenizer;
using Poco::InvalidToken;
using Poco::EOFToken;
using Poco::WhitespaceToken;
using Poco::Ascii;

#include "parser/Glyphe.h"

namespace Poco
{
namespace FSM
{
namespace PARSER
{
Glyphe::Glyphe()
{
    _opMap["["] = OPENBRACKET;
    _opMap["]"] = CLOSBRACKET;
    _opMap["("] = OPENPARENT;
    _opMap[")"] = CLOSPARENT;
    _opMap["{"] = OPENBRACE;
    _opMap["}"] = CLOSBRACE;
    _opMap["<"] = LT;
    _opMap["<="] = LE;
    _opMap["<<"] = SHL;
    _opMap["<<="] = SHL_ASSIGN;
    _opMap[">"] = GT;
    _opMap[">="] = GE;
    _opMap[">>"] = SHR;
    _opMap[">>="] = SHR_ASSIGN;
    _opMap["="] = ASSIGN;
    _opMap["=="] = EQ;
    _opMap["!"] = NOT;
    _opMap["!="] = NE;
    _opMap["&"] = BITAND;
    _opMap["&="] = BITAND_ASSIGN;
    _opMap["&&"] = AND;
    _opMap["|"] = BITOR;
    _opMap["|="] = BITOR_ASSIGN;
    _opMap["||"] = OR;
    _opMap["^"] = XOR;
    _opMap["^="] = XOR_ASSIGN;
    _opMap["~"] = COMPL;
	_opMap["*"] = STAR;
	_opMap["**"] = STARSTAR;
	_opMap["*="] = STAR_ASSIGN;
    _opMap["/"] = SLASH;
    _opMap["/="] = SLASH_ASSIGN;
    _opMap["+"] = PLUS;
    _opMap["+="] = PLUS_ASSIGN;
    _opMap["++"] = INCR;
    _opMap["-"] = MINUS;
    _opMap["-="] = MINUS_ASSIGN;
    _opMap["--"] = DECR;
    _opMap["->"] = ARROW;
    _opMap["%"] = MOD;
    _opMap["%="] = MOD_ASSIGN;
    _opMap[","] = COMMA;
    _opMap["."] = PERIOD;
    _opMap["..."] = ELLIPSIS;
    _opMap[":"] = COLON;
    _opMap["::"] = DBL_COLON;
    _opMap[";"] = SEMICOLON;
    _opMap["?"] = QUESTION;
    _opMap["%{"] = OPENCODE;
    _opMap["%}"] = CLOSCODE;
    _opMap["%%"] = FSM;
}


Glyphe::~Glyphe()
{
}


Token::Class Glyphe::tokenClass() const
{
    return Token::OPERATOR_TOKEN;
}


bool Glyphe::start(char c, std::istream& istr)
{
    _value = c;
    char next = (char) istr.peek();
    switch (_value[0])
    {
    case '[':
    case ']':
    case '(':
    case ')':
    case '{':
    case '}':
    case '<':
    case '>':
    case '=':
    case '!':
    case '&':
    case '|':
    case '*':
    case '+':
    case '-':
    case '^':
    case '~':
    case ',':
    case ':':
    case ';':
    case '%':
    case '?':
        return true;
    case '.':
        return !(next >= '0' && next <= '9');
    case '/':
        return !(next == '/' || next == '*');
    default:
        return false;
    }
}


void Glyphe::finish(std::istream& istr)
{
    int next = (char) istr.peek();
    switch (_value[0])
    {
    case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case ';':
    case '?':
    case '~':
    case ',':
        break;
    case '.':
        if (next == '.')
        {
            _value += (char) istr.get();
            if (istr.peek() != '.')  syntaxError(".", std::string(1, (char)istr.peek()));
            _value += (char) istr.get();
        }
        break;
    case ':':
        if (next == ':') _value += (char) istr.get();
        break;
    case '<':
        if (next == '<')
        {
            _value += (char) istr.get();
            next = (char) istr.peek();
        }
        if (next == '=') _value += (char) istr.get();
        break;
    case '>':
        if (next == '>')
        {
            _value += (char) istr.get();
            next = (char) istr.peek();
        }
        if (next == '=') _value += (char) istr.get();
        break;
    case '&':
        if (next == '&' || next == '=') _value += (char) istr.get();
        break;
    case '|':
        if (next == '|' || next == '=') _value += (char) istr.get();
        break;
    case '+':
        if (next == '+' || next == '=') _value += (char) istr.get();
        break;
    case '-':
        if (next == '-' || next == '=' || next == '>') _value += (char) istr.get();
        break;
    case '=':
    case '!':
    case '/':
    case '^':
		if (next == '=' || next == '%') _value += (char) istr.get();
		break;
	case '%':
        if (next == '=' || next == '{' || next == '}' || next == '%') _value += (char) istr.get();
        break;
	case '*':
		if (next == '*' || next == '=') _value += (char) istr.get();
		break;
	default:
        poco_bugcheck();
    }
}


int Glyphe::asInteger() const
{
    OpMap::const_iterator it = _opMap.find(_value);
    if (it != _opMap.end())
        return it->second;
    else
        return 0;
}


}
}
}
