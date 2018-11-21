#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include "Model.h"
#include "AnimatedPlayer.h"
#include "GameView.h"
#include "GUI.h"
#include "Texture.h"
#include "TextureHandler.h"

class View
{
	public:
		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;

		View();
		View(unsigned int, unsigned int, char*);
		~View();

		int init(Model* model);
		void Update(float);
		void Start();

	private:
		GameView* gView;
		GUI* gui;

		Model* activeMap;

        TextureHandler* textureHandler;
    
        int LoadMap(Model* map);
        int LoadPlayer(AnimatedPlayer* player);
        int InitGUI();
    
		int CreateWindow();
		int CreateSurface();
		int CreateRenderer();
		SDL_Texture* LoadTexture(char*);
		void LoadTextures();

		char* WINDOW_TITLE;

		float scale;

};
