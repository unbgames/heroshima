//
// Created by edgar on 25/05/18.
//

#ifndef SRC_STRUCTS_H
#define SRC_STRUCTS_H

#include <string>

using std::string;

struct Sprites{
    string sprite;
    int offset;
    int frameCount;
    float frameTime;

    Sprites(string sprite, int offset, int frameCount, float frameTime);
    Sprites();
};

struct Projectile{
    string sprite;
    float speed;
    int frameCount;
    float frameTime;

    Projectile(string sprite, float speed, int frameCount, float frameTime);
    Projectile();
};

enum Orientation { RIGHT, LEFT };

#endif //SRC_STRUCTS_H
