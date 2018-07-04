//
// Created by edgar on 04/07/18.
//

#ifndef SRC_BIGGUY_H
#define SRC_BIGGUY_H

#define SPEED 100
#define PLAYER_DISTANCE_OFFSET 60


#include "Enemy.h"

class BigGuy : public Enemy {
public:
    BigGuy(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance);

    void Update(float dt) override;

    void NotifyCollision(GameObject &other) override;

private:
    bool going;
    float maxDistance;
    Vec2 initialPosition;
    Timer attackingTimer, deadTimer, attackCooldown;

};


#endif //SRC_BIGGUY_H
