#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/regulator.h"

class Controller
{
public:
	Controller();
	~Controller();

	void Run();

private:

	void processOutput();
	void handleInput();

	Regulator regulator;
	bool shutdown;
};

#endif // CONTROLLER_H
