//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#ifndef POCO_FSM_PARSER_H_
#define POCO_FSM_PARSER_H_

#include <stack>
using std::stack;

#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/CountingStream.h"
using Poco::Logger;
using Poco::Path;
using Poco::File;
using Poco::CountingInputStream;

#include "Tokenizer.h"
#include "model/SMC.h"
#include "parser/Token.h"
#include "model/Operator.h"

using Poco::FSM::MODEL::StatePtr;
using Poco::FSM::MODEL::EntryPtr;
using Poco::FSM::MODEL::ExitPtr;
using Poco::FSM::MODEL::GuardPtr;
using Poco::FSM::MODEL::MapPtr;
using Poco::FSM::MODEL::ActionPtr;
using Poco::FSM::MODEL::TransitionPtr;
using Poco::FSM::MODEL::ParameterPtr;
using Poco::FSM::MODEL::FSMPtr;
using Poco::FSM::MODEL::ExpressionPtr;
using Poco::FSM::MODEL::ArgumentPtr;
using Poco::FSM::MODEL::ReferencePtr;
using Poco::FSM::MODEL::Operator;

namespace Poco {
	namespace FSM {
		namespace PARSER {

			class Parser {
			public:
				Parser(Logger& logger, const File& smfile, std::istream& istr);
				virtual ~Parser();
				FSMPtr parse(const Path& out);

			protected:
				const Token* parseAccess(const Token* next);
				const Token* parseAction(const Token* next);
				const Token* parseActions(const Token* next, List<ActionPtr>& actions);
				const Token* parseArgument(const Token* next, List<ArgumentPtr>& list);
				const Token* parseArguments(const Token* next, List<ArgumentPtr>& list);
				const Token* parseClass(const Token* next);
				const Token* parseDeclare(const Token* next);
				const Token* parseEntry(const Token* next);
				const Token* parseExit(const Token* next);
				const Token* parseExpression(const Token* next, ExpressionPtr& expression);
				const Token* parseFSM(const Token* next);
				const Token* parseFSMClass(const Token* next);
				const Token* parseFSMFile(const Token* next);
				const Token* parseFile(const Token* next, const Path& out);
				const Token* parseGuard(const Token* next);
				const Token* parseHeader(const Token* next);
				const Token* parseImport(const Token* next);
				const Token* parseInclude(const Token* next);
				const Token* parseIncludes(const Token* next);
				const Token* parseMap(const Token* next);
				const Token* parseNext(const Token* next);
				const Token* parsePackage(const Token* next);
				const Token* parseParameter(const Token* next);
				const Token* parseParameters(const Token* next);
				const Token* parsePopArguments(const Token* next);
				const Token* parsePopTransition(const Token* next);
				const Token* parsePushTransition(const Token* next);
				const Token* parseRawCode(const Token* next);
				const Token* parseReturn(const Token* next);
				const Token* parseSource(const Token* next);
				const Token* parseStart(const Token* next);
				const Token* parseState(const Token* next);
				const Token* parseStates(const Token* next);
				const Token* parseTransition(const Token* next);
				const Token* parseTransitionArgs(const Token* next);
				const Token* parseTransitions(const Token* next);
				const Token* parseTerminal(const Token* next, ReferencePtr& reference);

				static bool isString(const Token* token);
				static bool isCharacter(const Token* token);
				static bool isNumber(const Token* token);
				static bool isIdentifier(const Token* token);
				static bool isOperator(const Token* token);
				static bool isOperator(const Token* token, int kind);
				static bool isKeyword(const Token* token, int kind);
				static bool isEOF(const Token* token);
//				static void expectOperator(const Token* token, int kind, const string& msg);
				static void syntaxError(const string& msg);
//				static void append(string& decl, const string& token);
//				static void append(string& decl, const Token* token);
				static bool isOperator(ExpressionPtr expression, Operator op);


				const Token* nextToken();
				const Token* nextParserToken();
				void reduce();

			public:
				const File& file() const { return _file; }

			private:
				CountingInputStream _istr;
				Tokenizer			_tokenizer;
				File				_file;
				Path				_path;
				string				_currentPath;
				bool				_inFile;
				string				_package;
				string				_library;
				string				_doc;
				string				_attrs;

				FSMPtr				fsm;
				StatePtr			state;
				GuardPtr			guard;
				MapPtr				map;
				ActionPtr			action;
				TransitionPtr		transition;
				ParameterPtr		parameter;
				List<ParameterPtr>	 parameters;
				EntryPtr			entry;
				ExitPtr				exit;

				Logger&					_logger;
			};

		}
	}
}
#endif
