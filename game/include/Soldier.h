//
// Created by edgar on 09/07/18.
//

#ifndef SRC_SOLDIER_H
#define SRC_SOLDIER_H

#define SPEED 150
#define PLAYER_DISTANCE_OFFSET 500


#include "Enemy.h"

class Soldier : public Enemy {
public:
    Soldier(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance);

    void Update(float dt) override;

    void NotifyCollision(GameObject &other) override;

private:
    Timer idleTimer;

    bool going, damaged, canDamage;
    float maxDistance, verticalSpeed;
    Vec2 initialPosition, speed;
    Timer attackingTimer, deadTimer, attackCooldown, shootTimer;

    void Shoot(float angle);
};


#endif //SRC_SOLDIER_H
