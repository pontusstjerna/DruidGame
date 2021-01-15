#include "control/MainController.h"

int main(int argc, char *argv[])
{
	MainController *mainController = new MainController();
	mainController->start();

	delete mainController;

	return 0;
}
