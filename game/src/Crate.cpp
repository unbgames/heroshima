//
// Created by edgar on 28/05/18.
//

#include <Player.h>
#include <CollisionTile.h>
#include <Collider.h>
#include "Crate.h"

Crate::Crate(GameObject &associated, Vec2 position) : Component(associated), position(position) {
    associated.box.x = position.x;
    associated.box.y = -associated.box.h;
    associated.AddComponent(new Collider(associated));
}

void Crate::Update(float dt) {
    if(Player::player->GetAssociatedBox().x > associated.box.x - 400){
        verticalSpeed += GRAVITY * dt;
    }

    speed = Vec2(0, verticalSpeed);
    associated.box += speed;
}

void Crate::Render() {}

bool Crate::Is(string type) {
    return type == WEAPON_CRATE_TYPE;
}

void Crate::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile != nullptr) {
        associated.box.y =  other.box.y - associated.box.h;
        verticalSpeed = 0;
    }
}
