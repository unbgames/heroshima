//
// Created by edgar on 25/05/18.
//

#include "Gun.h"
#include <utility>

using std::move;

Gun::Gun(int damage, int ammo, float cooldownTime, Sprites spriteRest, Sprites spriteWalk,
         Sprites spriteShoot, Projectile projectile) :
        damage(damage), ammo(ammo), cooldownTime(cooldownTime), rest(move(spriteRest)), walk(move(spriteWalk)),
        shoot(move(spriteShoot)),projectile(move(projectile)), full(ammo) {}

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

int Gun::getFull() const {
    return full;
}

void Gun::setAmmo(int ammo) {
    Gun::ammo = ammo;
}

