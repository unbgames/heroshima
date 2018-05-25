//
// Created by edgar on 25/05/18.
//

#include "Gun.h"
#include <utility>

Gun::Gun(int damage, int ammo, float cooldownTime, const Sprites &spriteRest, const Sprites &spriteWalk,
         const Sprites &spriteShoot, const Projectile &projectile) : damage(damage), ammo(ammo),
                                                                               cooldownTime(cooldownTime),
                                                                               rest(spriteRest),
                                                                               walk(spriteWalk),
                                                                               shoot(spriteShoot),
                                                                               projectile(projectile) {}

Gun::Gun() {}

int Gun::getDamage() const {
    return damage;
}

int Gun::getAmmo() const {
    return ammo;
}

float Gun::getCooldownTime() const {
    return cooldownTime;
}

void Gun::decrementAmmo() {
    ammo--;
}

const Sprites &Gun::getSpriteRest() const {
    return rest;
}

const Sprites &Gun::getSpriteWalk() const {
    return walk;
}

const Sprites &Gun::getSpriteShoot() const {
    return shoot;
}

const Projectile &Gun::getProjectile() const {
    return projectile;
}

