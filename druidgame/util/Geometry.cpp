//
//  Geometry.cpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-27.
//  Copyright © 2018 nocroft. All rights reserved.
//

#include "Geometry.h"
#include <cmath>

float Geometry::distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
