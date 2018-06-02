//
// Created by edgar on 25/05/18.
//

#ifndef SRC_STRUCTS_H
#define SRC_STRUCTS_H

#include <string>

using std::string;

struct StaticSprite {
    string sprite;
    int offset;
    int frameCount;
    float frameTime;

    explicit StaticSprite(string sprite, int frameCount, float frameTime, int offset = 0);
    StaticSprite();
};

struct Projectile {
    string sprite;
    float speed;
    int frameCount;
    float frameTime;

    Projectile(string sprite, float speed, int frameCount, float frameTime);
    Projectile();
};

enum Orientation { RIGHT, LEFT };

#endif //SRC_STRUCTS_H
