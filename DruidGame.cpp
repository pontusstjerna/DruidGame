#include "MainController.h"

int main()
{
	MainController* mc = new MainController();
	mc->Start();

	delete mc;
	return 0;
}