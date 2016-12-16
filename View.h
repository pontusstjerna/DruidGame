#pragma once
#include <SDL.h>
#include <SDL_image.h>

class View
{
	public:
		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int InitView();
		void Update(int);

	private:
		int CreateWindow();
		int CreateSurface();
		int CreateRenderer();
		SDL_Texture* LoadTexture(char*);
		int View::InitSDLImage();

		const unsigned int WINDOW_WIDTH;
		const unsigned int WINDOW_HEIGHT;
		char* WINDOW_TITLE;

};
