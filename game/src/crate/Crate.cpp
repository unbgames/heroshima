//
// Created by edgar on 28/05/18.
//

#include <Player.h>
#include <CollisionTile.h>
#include <Collider.h>
#include <Gravity.h>
#include "Crate.h"

Crate::Crate(GameObject &associated, Vec2 initialPosition, bool startFalling) :
        Component(associated), fell(false) {
    associated.box.x = initialPosition.x;

    if(startFalling) {
        associated.box.y = -3*associated.box.h;
    } else{
        associated.box.y = initialPosition.y;
    }

    associated.AddComponent(new Collider(associated, {0.8, 0.8}));
}

void Crate::Update(float dt) {
    if(Player::player->GetAssociatedBox().x > associated.box.x - CRATE_OFFSET){
        if (!fell){
            fell = true;
            associated.AddComponent(new Gravity(associated));
        }
    }
}

void Crate::Render() {}

bool Crate::Is(string type) {
    return type == CRATE_TYPE;
}

void Crate::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile) {
        Component *gravity = associated.GetComponent(GRAVITY_TYPE);
        //Removes gravity after touch ground;
        if(gravity){associated.RemoveComponent(gravity);}
        associated.box.y =  other.box.y - associated.box.h;
    }

    auto player = (Player*) other.GetComponent(PLAYER_T);
    if(player){
        onCatch();
    }
}
