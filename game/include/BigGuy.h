//
// Created by edgar on 04/07/18.
//

#ifndef SRC_BIGGUY_H
#define SRC_BIGGUY_H

#define SPEED 100
#define PLAYER_DISTANCE_OFFSET 80


#include "Enemy.h"
#include "Sound.h"

class BigGuy : public Enemy {
public:
    BigGuy(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance);

    void Update(float dt) override;

    void NotifyCollision(GameObject &other) override;

private:
    Sound *walkSound, *explosionSound;

    bool going, damaged, canDamage;
    float maxDistance;
    Vec2 initialPosition;
    Timer attackingTimer, deadTimer, attackCooldown;

};


#endif //SRC_BIGGUY_H
