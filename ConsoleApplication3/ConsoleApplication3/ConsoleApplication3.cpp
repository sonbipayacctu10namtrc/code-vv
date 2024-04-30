#include "Controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(unsigned int(time(NULL)));

	Controller controller;
	controller.run();

	return EXIT_SUCCESS;
}