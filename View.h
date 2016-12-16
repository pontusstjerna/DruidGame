#pragma once
#include <SDL.h>

class View
{
	public:
		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int InitView();
		void Update(int);

	private:
		const unsigned int WINDOW_WIDTH;
		const unsigned int WINDOW_HEIGHT;
		char* WINDOW_TITLE;

};
