#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>
#include <time.h>

class Logger
{
public:
	static void info(std::string msg)  { log("INFO: "  + msg); }
	static void warn(std::string msg)  { log("WARN: "  + msg); }
	static void error(std::string msg) { log("ERROR: " + msg); }

private:
	Logger() {}
	static void log(std::string msg)
	{
		const std::string delim = "-------------------------------";
		std::ofstream logStream("logs/log.txt", std::ios::app);
		if (logStream.is_open())
		{
			logStream << delim << std::endl;
			logStream << "Time: " << getTimestamp() << std::endl;
			logStream << msg << std::endl ;
			logStream << delim << std::endl << std::endl;
			logStream.close();
		}
	}

	static std::string getTimestamp()
	{
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}
};

#endif