//
// Created by edgar on 28/05/18.
//

#include <Player.h>
#include <CollisionTile.h>
#include <Collider.h>
#include <Camera.h>
#include "Crate.h"

Crate::Crate(GameObject &associated, Vec2 initialPosition, bool startFalling) :
        Component(associated) {
    associated.box.x = initialPosition.x;

    if(startFalling) {
        associated.box.y = -3*associated.box.h;
    } else{
        associated.box.y = initialPosition.y;
    }

    associated.AddComponent(new Collider(associated));
}

void Crate::Update(float dt) {
    if(Player::player->GetAssociatedBox().x > associated.box.x - CRATE_OFFSET){
        verticalSpeed += GRAVITY * dt;
    }

    speed = Vec2(0, verticalSpeed);
    associated.box += speed;
}

void Crate::Render() {}

bool Crate::Is(string type) {
    return type == CRATE_TYPE;
}

void Crate::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile != nullptr) {
        associated.box.y =  other.box.y - associated.box.h;
        verticalSpeed = 0;
    }

    auto player = (Player*) other.GetComponent(PLAYER_T);
    if(player){
        onCatch();
    }
}
