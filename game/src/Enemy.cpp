//
// Created by edgar on 07/06/18.
//

#include "Enemy.h"

Enemy::Enemy(GameObject &associated, int hp) : Component(associated), hp(hp) {}

void Enemy::Start() {
    Component::Start();
}

void Enemy::Render() {
    if(state == E_WALKING ){
        Walk();
    } else if(state == E_STOPPED ){
        Stop();
    } else if(state == E_FALLING ){
        Fall();
    } else if(state == E_CHASING ){
        Chase();
    } else if(state == E_ATTACKING ){
        Attack();
    } else if(state == E_STUCK ){
        Stuck();
    } else if(state == E_DEAD){
        Die();
    }

}

bool Enemy::Is(string type) {
    return type == ENEMY_TYPE;
}

void Enemy::Walk() {}
void Enemy::Stop() {}
void Enemy::Fall() {}
void Enemy::Chase() {}
void Enemy::Attack() {}
void Enemy::Stuck() {}
void Enemy::Die() {}