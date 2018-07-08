//
// Created by edgar on 07/06/18.
//

#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#define SWORD_TRIGGER_DISTANCE 40

#define ENEMY_TYPE "Enemy"

#include "Component.h"
#include "Timer.h"

class Enemy : public Component {
public:
    explicit Enemy(GameObject &associated, int hp, Vec2 initialPosition);

    virtual ~Enemy();

    void Start() override;

    void Update(float dt) override = 0;
    void Render() override;
    bool Is(string type) override;

    EnemyState getState();
    int getHp();

protected:
    StaticSprite current;
    StaticSprite walking, idle, stopped, falling, chasing, attacking, stuck, deadByBullet, deadBySword, preparing;

    EnemyState state;
    int hp;

    GameObject *swordColliderLeft;
    GameObject *swordColliderRight;

    bool IsCloseEnoughToPlayer(float distance);

};


#endif //SRC_ENEMY_H
