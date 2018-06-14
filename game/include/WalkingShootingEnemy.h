//
// Created by edgar on 14/06/18.
//

#ifndef WALKINGSHOOTINGENEMY_H
#define WALKINGSHOOTINGENEMY_H

#define PLAYER_DISTANCE_OFFSET 450

#include <Enemy.h>

class WalkingShootingEnemy : public Enemy {
public:
    WalkingShootingEnemy(GameObject &associated, int hp, Vec2 initialPosition);

    void Update(float dt) override;

    void NotifyCollision(GameObject &other) override;

    void Shoot(float angle);

private:
    Timer attackingTimer, deadTimer;
};


#endif //SRC_WALKINGSHOOTINGENEMY_H
