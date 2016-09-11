//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//

#include <sstream>
#include <fstream>
#include <iostream>

using std::cout;
using std::cerr;
using std::clog;
using std::hex;
using std::endl;

#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Util/LoggingConfigurator.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/Exception.h"
#include "Poco/Thread.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/OptionCallback.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "model/SMC.h"
#include "model/Mode.h"
#include "model/FSM.h"
#include "model/Print.h"
#include "parser/Parser.h"

using Poco::Thread;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Util::LoggingConfigurator;
using Poco::Util::PropertyFileConfiguration;
using Poco::Path;
using Poco::File;
using Poco::FileStream;
using Poco::FileInputStream;
using Poco::FileOutputStream;

using Poco::FSM::PARSER::Parser;
using Poco::FSM::MODEL::Mode;
using Poco::FSM::MODEL::Print;

const static string NL = "\n";

class FSMCompiler: public Application
{
public:
    FSMCompiler() : help(false), verbose(false), debug(false)
    {

    }
protected:
    void initialize(Application& self)
    {
        loadConfiguration(); // load default configuration files, if present
        Application::initialize(self);
    }

    void uninitialize()
    {
        Application::uninitialize();
    }

    void reinitialize(Application& self)
    {
        Application::reinitialize(self);
    }
    void defineOptions(OptionSet& options)
    {
        Application::defineOptions(options);

        options.addOption(
            Option("help", "h",	"display help information on command line arguments")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<FSMCompiler>(this, &FSMCompiler::handleHelp)));

		options.addOption(
			Option("out", "o", "the out directory where to generate the c++ code, defaulted to the fsm file directory")
			.required(false)
			.repeatable(false)
			.argument("file")
			.callback(OptionCallback<FSMCompiler>(this, &FSMCompiler::handleOutdir)));

		options.addOption(
			Option("mode", "m", "either SMC, either ITU, defaulted to SMC")
			.required(false)
			.repeatable(false)
			.argument("mode", false)
			.callback(OptionCallback<FSMCompiler>(this, &FSMCompiler::hanldeMode)));

		options.addOption(
            Option("verbose", "v", "output the parsed FSM file on the console")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<FSMCompiler>(this, &FSMCompiler::handleVerbose)));

        options.addOption(
            Option("debug", "d", "generate debug log")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<FSMCompiler>(this, &FSMCompiler::handleDebug)));

    }

    void handleHelp(const std::string& name, const std::string& value)
    {
        help = true;
        displayHelp();
        stopOptionsProcessing();
    }

    void handleOutdir(const std::string& name, const std::string& value)
    {
        out = Path(value);
    }

	void handleVerbose(const std::string& name, const std::string& value)
	{
		verbose = true;
	}
	
	void hanldeMode(const std::string& name, const std::string& value)
	{
		if (value == "SMC")
			mode = value;
		else if (value == "ITU")
			mode = value;
		else {
			Logger& logger = Application::instance().logger();
			logger.information("invalid value for mode, defaulted to SMC");
			mode = "SMC";
		}
	}

    void handleDebug(const std::string& name, const std::string& value)
    {
        debug = true;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("<options> <fsm>.sm");
		helpFormatter.setHeader("A Finite State Machine compiler for the Poco stack.");
		helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args)
    {
        Logger& logger = Application::instance().logger();
        if (!help)
        {
            if (args.size() == 0)
            {
                logger.error("Missing FSM file");
                return Application::EXIT_NOINPUT;
            }
            path = args[0];
            if (!path.isFile())
            {
                logger.error("file %s is not a file", path.toString());
                return Application::EXIT_USAGE;
            }
			string extension = path.getExtension();
            if (!(extension == "sm" || extension == "smt" || extension == "smx"))
            {
                logger.error("file %s is not a FSM file", path.toString());
                return Application::EXIT_USAGE;
            }
            if (!out.isDirectory())
            {
                logger.error("%s is not a directory", out.toString());
                return Application::EXIT_USAGE;
            }
            if (out.depth() <= 0)
            {
                out = path;
                out = out.makeParent();
            }
            file = File(path.makeAbsolute());
            logger.information("fsmc %s", path.toString());

            FileInputStream fis(path.toString());
            Parser parser(logger, file, fis, mode == "ITU" ? Mode::ITU : Mode::SMC);
            FSMPtr fsm;

            fsm = parser.parse(out);
            if (fsm && !fsm->updated())
            {
                Print print(logger);
                if (verbose)
                    fsm->print(print);
                fsm->generate(out, debug);
            }
        }
        return Application::EXIT_OK;
    }

private:
    bool	help;
    bool	verbose;
    bool	debug;
    Path	out;
    Path	path;
    File	file;
	string	mode;
};
POCO_APP_MAIN(FSMCompiler)
