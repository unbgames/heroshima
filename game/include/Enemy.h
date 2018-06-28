//
// Created by edgar on 07/06/18.
//

#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#define ENEMY_TYPE "Enemy"

#include "Component.h"

class Enemy : public Component {
public:
    explicit Enemy(GameObject &associated, int hp, Vec2 initialPosition);

    void Start() override;

    void Update(float dt) override = 0;
    void Render() override;
    bool Is(string type) override;

    EnemyState getState();
    int getHp();

protected:
    StaticSprite current;
    StaticSprite walking, idle, stopped, falling, chasing, attacking, stuck, dead, preparing;

    EnemyState state;
    int hp;

};


#endif //SRC_ENEMY_H
