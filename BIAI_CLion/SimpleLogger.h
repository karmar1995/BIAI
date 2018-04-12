#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H

#include <cstdlib>
#include <iostream>

enum OutStream{cout, cerr, clog};

class SimpleLogger
{
public:
	SimpleLogger();
	~SimpleLogger();
	void PrintLog(OutStream stream, ...);
};


#endif