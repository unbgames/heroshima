//
// Created by edgar on 25/05/18.
//

#include "Structs.h"

StaticSprite::StaticSprite(string sprite, int frameCount, float frameTime, int offset)
        : sprite(sprite), offset(offset), frameCount(frameCount), frameTime(frameTime) {}

StaticSprite::StaticSprite() {}

Projectile::Projectile(string sprite, float speed, int frameCount, float frameTime) : sprite(sprite), speed(speed), frameCount(frameCount), frameTime(frameTime) {}

Projectile::Projectile() {}

Edge::Edge(bool right, bool left, bool top, bool bottom) : RIGHT(right), LEFT(left), TOP(top), BOTTOM(bottom) {}

Edge::Edge() {}

string Edge::toString() const {
    char buffer [50];
    sprintf (buffer, "(right: %d, left: %d, top: %d, bottom: %d)", RIGHT, LEFT, TOP, BOTTOM);
    return buffer;
}
