//
// Created by edgar on 07/06/18.
//

#include <engine/components/Collider.h>
#include <engine/components/Sprite.h>
#include "enemy/Enemy.h"

Enemy::Enemy(GameObject &associated, int hp) : Component(associated), hp(hp) {
    associated.AddComponent(new Collider(associated));
}

void Enemy::Start() {
    Component::Start();
}

void Enemy::Render() {
    if(state == E_WALKING ){
        current = walking;
        cout<<"walking"<<endl;
    } else if(state == E_IDLE ){
        current = idle;
        cout<<"idle"<<endl;
    } else if(state == E_STOPPED ){
        current = stopped;
        cout<<"stopped"<<endl;
    } else if(state == E_FALLING ){
        current = falling;
        cout<<"falling"<<endl;
    } else if(state == E_CHASING ){
        current = chasing;
        cout<<"chasing"<<endl;
    } else if(state == E_ATTACKING ){
        current = attacking;
        cout<<"attacking"<<endl;
    } else if(state == E_STUCK ){
        current = stuck;
        cout<<"stuck"<<endl;
    } else if(state == E_DEAD){
        current = dead;
        cout<<"dead"<<endl;
    } else if(state == E_PREPARING){
        current = preparing;
        cout<<"preparing"<<endl;
    }

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    sprite->Open(current.sprite);
    sprite->SetFrameCount(current.frameCount);
    sprite->SetFrameTime(current.frameTime);

//    auto collider = (Collider*)associated.GetComponent(COLLIDER_TYPE);
//    if(collider){
//        collider->setScale({sprite->GetWidth(), sprite->GetHeight()});
//    }
}

bool Enemy::Is(string type) {
    return type == ENEMY_TYPE;
}

EnemyState Enemy::getState() {
    return state;
}

int Enemy::getHp() {
    return hp;
}
