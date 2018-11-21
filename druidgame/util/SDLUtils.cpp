//
//  SDLUtils.cpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-21.
//  Copyright © 2018 nocroft. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "SDLUtils.h"

int SDLUtils::initSDLImage() {
    int imgFlags = IMG_INIT_PNG;
    
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }
    
    return 0;
}
