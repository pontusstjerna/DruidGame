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
    
    for (const auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
        printf("Destroyed texture %s.\n", texture.first);
    }
    
    textures.clear();
}

SDL_Texture* TextureHandler::getTexture(char const* name) {
    
    auto search = textures.find(name);
    if (search != textures.end()) { // Found it
        return search->second;
    }
    
    return load(name);
}

SDL_Texture* TextureHandler::load(char const* name) {
    
    SDL_Texture* texture = NULL;
    
    SDL_Surface* tmpSurface = IMG_Load(name);
    
    if (tmpSurface == NULL) {
        printf("Unable to load image: %s. \nCause: %s\n", name, SDL_GetError());
        return NULL;
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    
    if (texture == NULL) {
        printf("Unable to load texture. \nCause: %s\n", SDL_GetError());
        return NULL;
    }
    
    
    //Reallocate
    SDL_FreeSurface(tmpSurface);
    
    printf("Loaded texture %s. \n", name);
    
    //Add texture to texture list
    textures[name] = texture;
    
    return texture;
}
