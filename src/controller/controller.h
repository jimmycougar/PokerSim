#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model/regulator.h"

class Controller
{
public:
	Controller(Observer * inView, Regulator * inRegulator);
	~Controller();

	void Run();

private:

	Observer * view;
	Regulator * regulator;
};

#endif // CONTROLLER_H
