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
#include <SDL2/SDL_image.h>

class TextureHandler {
public:
    TextureHandler(SDL_Renderer* renderer);
    ~TextureHandler();
    
    // void loadTextures();
    SDL_Texture* getTexture(char const* name);
    
private:
    std::map<char const*, SDL_Texture*> textures;
    SDL_Texture* load(char const* name);
    SDL_Renderer* renderer;
};

#endif /* TextureHandler_h */
