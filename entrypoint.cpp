/** entrypoint.cpp
  */

/** TODO
	- //+TODO-C++17 Update compiler (C++17 needed)
  */

#include "progArgs.h"
#include <chrono>
#include <cstdio>
//+TODO-C++17 #include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;
using namespace Utilities;
//+TODO-C++17 namespace fs = std::filesystem;


/// Command line parameters

struct CmdLineParams
{
	std::string   source,
	              dest;
	std::string   configFile;
	milliseconds  interval   = milliseconds(1000);
	size_t        maxSizeKB  = 16;
};


void PrintHelp();
int ReadCommandLineParams(CmdLineParams &clp, int argc, char* argv[]);
int GetJsonParams(CmdLineParams &clp) { return -1; } //+TODO


int main(int argc, char* argv[])
{
	CmdLineParams clp;
	ReadCommandLineParams(clp, argc, argv);

	std::ifstream ifs(clp.source);
	std::ofstream ofs(clp.dest, std::ios_base::app | std::ios_base::out);

	while(true)
	{
		while(!ifs.is_open()) {
			// Wait for input file to be available
			std::this_thread::sleep_for(clp.interval);
			ifs.open(clp.source);
		}

		ofs << ifs.rdbuf() << std::flush;

		// Truncate input file to 0, i.e. delete it
		//+TODO-C++17 fs::resize_file(clp.source, 0); ifs.seekg(0);
		std::remove(clp.source.c_str());

		//+TODO - If changed, reload JSON parameters
		//+TODO - Check for exit conditions

		std::this_thread::sleep_for(clp.interval);
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


/// Read command line parameters

int ReadCommandLineParams(CmdLineParams &clp, int argc, char* argv[])
{
	ProgArgs            arguments;
	ProgArgs::Argument  arg;

	arg.Set("--source", "-s", "path of the source file on a temporary device", false, true, "test0.txt");
	arguments.AddArg(arg);
	arg.Set("--dest", "-d", "path of the destination file on a permanent device", false, true, "test.txt");
	arguments.AddArg(arg);
	arg.Set("--interval", "-i", "time interval between checks (in seconds)", true, true, std::to_string(clp.interval.count()));
	arguments.AddArg(arg);
	arg.Set("--maxsize", "-m", "source file size that triggers the move (in KB)", true, true, std::to_string((clp.maxSizeKB)));
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

	if(arguments.GetValue("--config")) {
		bool r = arguments.GetValue("--config", clp.configFile);
		if(r == true)
			GetJsonParams(clp);
	}

	arguments.GetValue("--source", clp.source);
	arguments.GetValue("--dest", clp.dest);
	int interval;
	arguments.GetValue("--interval", interval);
	clp.interval = std::chrono::milliseconds(1000*interval);
	arguments.GetValue("--maxsize", clp.maxSizeKB);

	return 0;
}


