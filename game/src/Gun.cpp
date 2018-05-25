//
// Created by edgar on 25/05/18.
//

#include "Gun.h"
#include <utility>

Gun::Gun(int damage, int ammo, float cooldownTime, const Sprites &spriteRest, const Sprites &spriteWalk,
         const Sprites &spriteShoot, const Projectile &projectile) : damage(damage), ammo(ammo),
                                                                               cooldownTime(cooldownTime),
                                                                               spriteRest(spriteRest),
                                                                               spriteWalk(spriteWalk),
                                                                               spriteShoot(spriteShoot),
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

//Sprites
Sprites::Sprites(string sprite, int offset, int frameCount, float frameTime): sprite(sprite), offset(offset), frameCount(frameCount), frameTime(frameTime) {}

Sprites::Sprites() {}

const Sprites &Gun::getSpriteRest() const {
    return spriteRest;
}

const Sprites &Gun::getSpriteWalk() const {
    return spriteWalk;
}

const Sprites &Gun::getSpriteShoot() const {
    return spriteShoot;
}

//Projectile
Projectile::Projectile(string sprite, float speed, int frameCount, float frameTime) : sprite(sprite), speed(speed), frameCount(frameCount), frameTime(frameTime) {}

Projectile::Projectile() {}

const Projectile &Gun::getProjectile() const {
    return projectile;
}

