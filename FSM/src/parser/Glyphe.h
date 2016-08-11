//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef POCO_FSM_PARSER_GLYPHE_H_
#define POCO_FSM_PARSER_GLYPHE_H_

#include <map>
using std::map;
#include "parser/Token.h"

namespace Poco {
	namespace FSM {
		namespace PARSER {

			class Glyphe : public Token {
			public:
				enum OP	{
					OPENBRACKET = 1,// [
					CLOSBRACKET,    // ]
					OPENPARENT,     // (
					CLOSPARENT,     // )
					OPENBRACE,      // {
					CLOSBRACE,      // }
					LT,             // <
					LE,             // <=
					SHL,            // <<
					SHL_ASSIGN,		// <<=
					GT,				// >
					GE,             // >=
					SHR,            // >>
					SHR_ASSIGN,     // >>=
					ASSIGN,         // =
					EQ,             // ==
					NOT,            // !
					NE,             // !=
					BITAND,         // &
					BITAND_ASSIGN,  // &=
					AND,            // &&
					BITOR,          // |
					BITOR_ASSIGN,   // |= 
					OR,             // ||
					XOR,            // ^
					XOR_ASSIGN,     // ^=
					COMPL,          // ~
					STAR,		    // *
					STARSTAR,	    // **
					STAR_ASSIGN,	// *=
					SLASH,          // /
					SLASH_ASSIGN,   // /=
					PLUS,           // +
					PLUS_ASSIGN,    // +=
					INCR,           // ++
					MINUS,          // -
					MINUS_ASSIGN,   // -=
					DECR,           // --
					ARROW,          // ->
					MOD,            // %
					MOD_ASSIGN,     // %=
					COMMA,          // ,
					PERIOD,         // .
					ELLIPSIS,		// ...
					COLON,          // :
					DBL_COLON,      // ::
					SEMICOLON,      // ;
					QUESTION,       // ?
					OPENCODE,		// %{
					CLOSCODE,		// %}
					FSM				// %%
				};

				Glyphe();
				~Glyphe();
				Poco::Token::Class tokenClass() const;
				bool start(char c, std::istream& istr);
				void finish(std::istream& istr);
				int asInteger() const;

			private:
				typedef map<std::string, int> OpMap;

				OpMap _opMap;
			};

		}
	}
}
#endif
