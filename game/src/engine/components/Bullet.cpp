//
// Created by edgar on 19/04/18.
//

#include <Player.h>
#include <Sound.h>
#include <Game.h>
#include <MathUtil.h>
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"

Bullet::Bullet(GameObject &associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               string sprite,
               int frameCount,
               float frameTime,
               bool targetsPlayer) : Component(associated) {

    this->damage = damage;
    this->targetsPlayer = targetsPlayer;

    associated.AddComponent(new Sprite(associated, move(sprite), frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
    associated.angleDeg = angle;
    this->speed = Vec2(speed, 0).RotateDeg(angle);
    this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
    associated.box += speed * dt;
    distanceLeft -= (speed * dt).Mag();
    if(distanceLeft < 0){
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return type == BULLET_TYPE;
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject &other) {
    if(!other.GetComponent(PLAYER_T) && !other.GetComponent(PLAYER_ARMS_TYPE) && !other.GetComponent(BULLET_TYPE) && !targetsPlayer){
        //Player's bullet that hits everything but player's parts and bullets
        associated.RequestDelete();
        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, "img/penguindeath.png", 5, 0.1, 0.5));
        explosionGO->box.x = associated.box.GetCenter().x - explosionGO->box.w/2 + MathUtil::floatRand(-10, 10);
        explosionGO->box.y = associated.box.GetCenter().y - explosionGO->box.h/2 + MathUtil::floatRand(-10, 10);

        Game::GetInstance().GetCurrentState().AddObject(explosionGO);
    }
}
