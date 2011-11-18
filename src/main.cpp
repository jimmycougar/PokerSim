#include <iostream>
#include <time.h>
#include <cstdlib>

#include "controller/controller.h"
#include "view/textview.h"
#include "model/regulator.h"

int main()
{
	srand(time(NULL));
	TextView view;
	Regulator reg;
	Controller controller(&view, &reg);			
	controller.Run();
	return 0;
}
