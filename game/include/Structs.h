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

struct Edge {
    bool RIGHT;
    bool LEFT;
    bool TOP;
    bool BOTTOM;

    Edge(bool right, bool left, bool top, bool bottom);
    Edge();
    string toString() const;
};

enum Orientation { RIGHT, LEFT };

enum MoveState { WALKING, IDLE, CROUCH, BLOCKED_LEFT, BLOCKED_RIGHT, SWORD_ATTACK };

enum JumpState { JUMPING, FALLING, ONGROUND, LANDING };

enum BodyState { TRANSFORMING, INITIAL, DAMAGED, DEFAULT };

enum EnemyState { E_WALKING, E_IDLE, E_STOPPED, E_FALLING, E_CHASING, E_ATTACKING, E_STUCK, E_DEAD_BY_BULLET, E_DEAD_BY_SWORD, E_PREPARING };

#endif //SRC_STRUCTS_H