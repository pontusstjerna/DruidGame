//
//  TextureHandler.hpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-21.
//  Copyright © 2018 nocroft. All rights reserved.
//

#ifndef TextureHandler_h
#define TextureHandler_h

#include <stdio.h>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class TextureHandler {
public:
    TextureHandler(SDL_Renderer* renderer);
    ~TextureHandler();
    
    // void loadTextures();
    SDL_Texture* getTexture(char* name);
    
private:
    std::map<char*, SDL_Texture*> textures;
    SDL_Texture* load(char* name);
    SDL_Renderer* renderer;
};

#endif /* TextureHandler_h */
