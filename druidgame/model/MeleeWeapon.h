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
    MeleeWeapon(float dmg, float range, float strength, float haste);
    void update(float dTime);
    bool attack();
    float getDoneDmg(float distance);
    float getDmg();
    float getRange();
    float getStrength();
    
private:
    float const ATTACK_POINT = 100;
    
    float dmg;
    float range;
    float strength;
    float haste;
    
    float timer;
    bool attacked = false;
};

#endif /* Weapon_h */
