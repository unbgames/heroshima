//
// Created by edgar on 25/05/18.
//

#include "Gun.h"
#include <utility>

Gun::Gun() {}

Gun::Gun(int damage, int ammo, string sprite, int spriteOffset, int spriteFrameCount, float spriteFrameTime,
         float cooldownTime, float projectileSpeed, int projectileFrameCount, float projectileFrameTime) : damage(damage),
                                                                                                           ammo(ammo), sprite(std::move(sprite)), spriteOffset(spriteOffset), spriteFrameCount(spriteFrameCount), spriteFrameTime(spriteFrameTime),
                                                                                                           cooldownTime(cooldownTime),
                                                                                                           projectileSpeed(projectileSpeed),
                                                                                                           projectileFrameCount(projectileFrameCount),
                                                                                                           projectileFrameTime(projectileFrameTime) {

}

int Gun::getDamage() const {
    return damage;
}

int Gun::getAmmo() const {
    return ammo;
}

const string &Gun::getSprite() const {
    return sprite;
}

int Gun::getSpriteOffset() const {
    return spriteOffset;
}

int Gun::getSpriteFrameCount() const {
    return spriteFrameCount;
}

float Gun::getSpriteFrameTime() const {
    return spriteFrameTime;
}

float Gun::getCooldownTime() const {
    return cooldownTime;
}

float Gun::getProjectileSpeed() const {
    return projectileSpeed;
}

int Gun::getProjectileFrameCount() const {
    return projectileFrameCount;
}

float Gun::getProjectileFrameTime() const {
    return projectileFrameTime;
}

void Gun::decrementAmmo() {
    ammo--;
}

