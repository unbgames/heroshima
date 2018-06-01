//
// Created by edgar on 25/05/18.
//

#include "Structs.h"

StaticSprite::StaticSprite(string sprite, int offset, int frameCount, float frameTime): sprite(sprite), offset(offset), frameCount(frameCount), frameTime(frameTime) {}

StaticSprite::StaticSprite() {}

Projectile::Projectile(string sprite, float speed, int frameCount, float frameTime) : sprite(sprite), speed(speed), frameCount(frameCount), frameTime(frameTime) {}

Projectile::Projectile() {}