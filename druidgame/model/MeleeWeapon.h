//
//  Weapon.hpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-27.
//  Copyright © 2018 nocroft. All rights reserved.
//

#ifndef Weapon_h
#define Weapon_h

#include <stdio.h>

class MeleeWeapon {
    
public:
    float const ATTACK_POINT = 100;
    
    MeleeWeapon(float dmg, float range, float strength, float haste);
    void update(float dTime);
    bool attack();
    float getDoneDmg(float distance);
    float getDmg();
    float getRange();
    float getStrength();
    float getTimer();
    
private:
    float dmg;
    float range;
    float strength;
    float haste;
    
    float timer = ATTACK_POINT;
    bool attacked = false;
};

#endif /* Weapon_h */
