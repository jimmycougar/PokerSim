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
	Regulator regulator;
};

#endif // CONTROLLER_H
