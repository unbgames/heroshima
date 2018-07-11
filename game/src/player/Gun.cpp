//
// Created by edgar on 25/05/18.
//

#include "Gun.h"
#include <utility>

using std::move;

Gun::Gun(int damage, int ammo, float cooldownTime, StaticSprite spriteRest, StaticSprite spriteWalk,
         StaticSprite spriteShoot, StaticSprite crouch, Projectile projectile) :
        damage(damage), ammo(ammo), cooldownTime(cooldownTime), rest(move(spriteRest)), walk(move(spriteWalk)),
        shoot(move(spriteShoot)), crouch(move(crouch)) {

    this->projectile = move(projectile);
    this->full = ammo;
}

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

const StaticSprite &Gun::getSpriteRest() const {
    return rest;
}

const StaticSprite &Gun::getSpriteWalk() const {
    return walk;
}

const StaticSprite &Gun::getSpriteShoot() const {
    return shoot;
}

const StaticSprite &Gun::getSpriteCrouch() const {
    return crouch;
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

