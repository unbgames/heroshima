//
// Created by edgar on 19/04/18.
//

#include <Game.h>
#include <MathUtil.h>
#include <CollisionTile.h>
#include <Enemy.h>
#include <Sprite.h>
#include <Player.h>
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
               bool targetsPlayer) : Component(associated), angle(angle) {

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
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile) {
        Explode();
    }

    if(other.GetComponent(ENEMY_TYPE) && !other.GetComponent(BULLET_TYPE) && !targetsPlayer){
        Explode();

    }

    if(other.GetComponent(PLAYER_TYPE) && !other.GetComponent(BULLET_TYPE) && targetsPlayer){
        Explode();
    }
}

void Bullet::Explode() const {
    associated.RequestDelete();
    auto explosionGO(new GameObject());
    explosionGO->AddComponent(new Sprite(*explosionGO, "img/impact.png", 3, 0.05, 0.15));
    explosionGO->orientation = (angle == 0 ? RIGHT : LEFT);
    explosionGO->box.x = associated.box.GetCenter().x - explosionGO->box.w / 2 /*+ MathUtil::floatRand(-10, 10)*/;
    explosionGO->box.y = associated.box.GetCenter().y - explosionGO->box.h / 2 + MathUtil::floatRand(-10, 10);

    Game::GetInstance().GetCurrentState().AddObject(explosionGO);
}
