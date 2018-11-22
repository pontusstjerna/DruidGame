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

#include "Texture.h"

class TextureHandler {
public:
    TextureHandler(SDL_Renderer* renderer);
    ~TextureHandler();
    
    // void loadTextures();
    Texture* getTexture(char* name);
    
private:
    std::map<char*, Texture*> textures;
    Texture* load(char* name);
    SDL_Renderer* renderer;
};

#endif /* TextureHandler_h */
