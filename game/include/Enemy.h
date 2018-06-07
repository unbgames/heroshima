//
// Created by edgar on 07/06/18.
//

#ifndef SRC_ENEMY_H
#define SRC_ENEMY_H

#define ENEMY_TYPE "Enemy"


#include "Component.h"

class Enemy : public Component {
public:
    Enemy(GameObject &associated, int hp);

    void Start() override;

    void Update(float dt) override = 0;
    void Render() override;
    bool Is(string type) override;

protected:
    EnemyState state;
    int hp;

    void Walk();
    void Stop();
    void Fall();
    void Chase();
    void Attack();
    void Stuck();
    void Die();

};


#endif //SRC_ENEMY_H
