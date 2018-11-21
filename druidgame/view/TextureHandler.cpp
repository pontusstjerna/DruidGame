//
//  TextureHandler.cpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-21.
//  Copyright © 2018 nocroft. All rights reserved.
//

#include "TextureHandler.h"

TextureHandler::TextureHandler(SDL_Renderer* renderer) : renderer(renderer) {
    
}

TextureHandler::~TextureHandler() {
    textures.clear();
}

Texture* TextureHandler::getTexture(char *name) {
    
    auto search = textures.find(name);
    if (search != textures.end()) { // Found it
        return search->second;
    }
    
    return load(name);
}

Texture* TextureHandler::load(char* name) {
    
    SDL_Texture* sdlTexture = NULL;
    
    SDL_Surface* tmpSurface = IMG_Load(name);
    
    if (tmpSurface == NULL)
        printf("Unable to load image: %s. \nCause: %s\n", name, SDL_GetError());
    
    sdlTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    if (sdlTexture == NULL)
        printf("Unable to load texture. \nCause: %s\n", SDL_GetError());
    
    //Reallocate
    SDL_FreeSurface(tmpSurface);
    
    Texture* texture = new Texture(sdlTexture, name);
    
    //Add texture to texture list
    textures[name] = texture;
    
    return texture;
}