//
//  Weapon.cpp
//  druidgame
//
//  Created by Pontus Stjernström on 2018-11-27.
//  Copyright © 2018 nocroft. All rights reserved.
//

#include "MeleeWeapon.h"
#include "../util/Geometry.h"

MeleeWeapon::MeleeWeapon(float dmg, float range, float haste, float strength) :
dmg(dmg), range(range), haste(haste), strength(strength) {
    
}

void MeleeWeapon::update(float dTime) {
    timer -= dTime;
    
    if (timer < ATTACK_POINT) {
        timer += dTime * haste * 0.2;
    } else {
        timer = ATTACK_POINT;
    }
}

bool MeleeWeapon::attack() {
    if (timer >= ATTACK_POINT) { // Attack
        timer = 0;
        return true;
    }
    
    return false;
}

float MeleeWeapon::getDoneDmg(float distance) {
    if (timer >= distance <= range) {
        return dmg;
    }
    
    return 0;
}

float MeleeWeapon::getDmg() {
    return dmg;
}

float MeleeWeapon::getRange() {
    return range;
}

float MeleeWeapon::getStrength() {
    return strength;
}

bool MeleeWeapon::getOnCooldown() {
    return onCooldown;
}
