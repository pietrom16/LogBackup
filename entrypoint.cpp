/** entrypoint.cpp
  */

#include "progArgs.h"
#include <iostream>
#include <string>

using namespace Utilities;


/// Command line parameters

struct CmdLineParams
{
	std::string source,
	            dest;
	std::string configFile;
	float       interval = 1.0f;	// seconds
	size_t      maxSize  = 16;		// KB
};


void PrintHelp();


int main(int argc, char* argv[])
{
	/// Command line parameters
	{
		ProgArgs            arguments;
		ProgArgs::Argument  arg;

		arg.Set("--source", "-s", "path of the source file on a temporary device", false, true, "test.txt");
		arguments.AddArg(arg);
		arg.Set("--dest", "-d", "path of the destination file on a permanent device", false, true, "test2.txt");
		arguments.AddArg(arg);
		arg.Set("--interval", "-i", "time interval between checks (in seconds)", true, true, "1.0");
		arguments.AddArg(arg);
		arg.Set("--maxsize", "-m", "source file size that triggers the move (in KB)", true, true, "8");
		arguments.AddArg(arg);
		arg.Set("--config", "-c", "configuration file (JSON format) with parameters that can change during the run", true, false);
		arguments.AddArg(arg);
		arg.Set("--help", "-h", "this help message");
		arguments.AddArg(arg);

		arguments.Parse(argc, argv);		// load and parse the parameters passed by the user

		std::string value;

		if(arguments.GetValue("--help")) {
			PrintHelp();
			arguments.Help();
			exit(0);
		}
	}


	return 0;
}



void PrintHelp()
{
	std::cout << "LogBackup\n"
	    << "\n"
	    << "Copyright (C) 2017 Pietro Mele\n"
	    << "Released under a GPL 3 license.\n"
	    << "Web site:  https://github.com/pietrom16" << std::endl;

	//+TODO - Print description
	std::cout << "\n"
	             "Utility to move a file appending it to another file.\n"
	             "\n"
	             "Used to move logs from one disk to another, typically from a RAM-disk to a hard disk.\n"
				 "\n"
				 "Once launched, it runs in the background.\n"
				 "\n"
				 "* Syntax:\n"
				 "\n"
				 "	 `logbkp --source SRC --dest DEST --interval TIME_INT --maxsize MAX_SIZE`\n"
				 "	 `       --config CONFIG_FILE`\n"
				 "\n"
				 "	 `logbkp -s SRC -d DEST -i TIME_INT -m MAX_SIZE -c CONFIG_FILE`\n"
				 ;

	std::cout << std::endl;
}
