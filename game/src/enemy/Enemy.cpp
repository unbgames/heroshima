//
// Created by edgar on 07/06/18.
//

#include <Collider.h>
#include <Sprite.h>
#include <Game.h>
#include <Player.h>
#include "Enemy.h"

Enemy::Enemy(GameObject &associated, int hp, Vec2 initialPosition) : Component(associated), hp(hp) {
    associated.AddComponent(new Collider(associated));
    associated.box += initialPosition;
}

void Enemy::Start() {
    Component::Start();
}

void Enemy::Render() {
    if(state == E_WALKING ){
        current = walking;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"walking"<<endl;
    } else if(state == E_IDLE ){
        current = idle;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"idle"<<endl;
    } else if(state == E_STOPPED ){
        current = stopped;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"stopped"<<endl;
    } else if(state == E_FALLING ){
        current = falling;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"falling"<<endl;
    } else if(state == E_CHASING ){
        current = chasing;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"chasing"<<endl;
    } else if(state == E_ATTACKING ){
        current = attacking;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"attacking"<<endl;
    } else if(state == E_STUCK ){
        current = stuck;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"stuck"<<endl;
    } else if(state == E_DEAD_BY_BULLET){
        current = deadByBullet;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"deadByBullet"<<endl;
    } else if(state == E_DEAD_BY_SWORD){
        current = deadBySword;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"deadBySword"<<endl;
    } else if(state == E_PREPARING){
        current = preparing;
//        if(Game::GetInstance().GetCurrentState().isDebug()) cout<<"preparing"<<endl;
    }

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    sprite->Open(current.sprite);
    sprite->SetFrameCount(current.frameCount);
    sprite->SetFrameTime(current.frameTime);

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

bool Enemy::IsCloseEnoughToPlayer(float distance) {
    auto playerBox = Player::player->GetAssociatedBox();
    return (associated.box.x > playerBox.x - distance - associated.box.w/2 && associated.box.x < playerBox.x + distance);
}
