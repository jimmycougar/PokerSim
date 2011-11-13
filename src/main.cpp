#include <iostream>
#include <time.h>
#include <cstdlib>

#include "controller/controller.h"

int main()
{
	srand(time(NULL));
	Controller controller;			
	controller.Run();
	return 0;
}
