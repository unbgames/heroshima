//
// Created by edgar on 07/06/18.
//

#include <Sprite.h>
#include <Gravity.h>
#include <CollisionTile.h>
#include <Player.h>
#include "Enemy1.h"

Enemy1::Enemy1(GameObject &associated, int hp, Vec2 initialPosition, bool startFalling)
        : Enemy(associated, hp), fell(false), onGroud(false), hit(false), speed({0, 0}) {

    falling = StaticSprite("img/enemy_falling.png", 2, 0.3f);
    walking = StaticSprite("img/enemy_running.png", 12, 0.06f);
    idle = StaticSprite("img/enemy_idle.png", 6, 0.2f);
    stopped = StaticSprite("img/enemy_idle.png", 6, 0.2f);
    preparing = StaticSprite("img/enemy_preparing.png", 4, 0.1f);
    attacking = StaticSprite("img/enemy_attacking.png", 8, 0.1f, 60);

    state = E_STOPPED;

    Sprite* img = new Sprite(associated, idle.sprite, idle.frameCount, idle.frameTime);
    if(startFalling){
        associated.box = {initialPosition.x, -3*associated.box.h, img->GetWidth(), img->GetHeight()};
    } else{
        associated.box = {initialPosition.x, initialPosition.y, img->GetWidth(), img->GetHeight()};
    }
    associated.orientation = LEFT;
    associated.AddComponent(img);
}

void Enemy1::Update(float dt) {
    auto playerBox = Player::player->GetAssociatedBox();

    if(state == E_STOPPED) {
        if (playerBox.x > associated.box.x - PLAYER_DISTANCE_OFFSET && !fell) {
            state = E_FALLING;
            if (!fell && !onGroud) {
                fell = true;
                associated.AddComponent(new Gravity(associated));
            }
        }
    }

    else if(state == E_IDLE){
        hit = false;
        idleTimer.Update(dt);
        if(idleTimer.Get() > IDLE_TIME){
            state = E_WALKING;
            idleTimer.Restart();
        }
    }

    else if(state == E_WALKING){
        if(!(associated.box.x > playerBox.x - PLAYER_DISTANCE_THRESHOLD - associated.box.w/2 && associated.box.x < playerBox.x + PLAYER_DISTANCE_THRESHOLD)) {
            if (associated.box.x > playerBox.x + PLAYER_DISTANCE_THRESHOLD) {
                associated.orientation = RIGHT;
                associated.box.x -= SPEED * dt;
            } else if (associated.box.x < playerBox.x - PLAYER_DISTANCE_THRESHOLD + associated.box.w/2) {
                associated.orientation = LEFT;
                associated.box.x += SPEED * dt;
            }
        } else{
           state = E_PREPARING;
        }
    }

    else if(state == E_PREPARING){
        preparingTimer.Update(dt);
        if(preparingTimer.Get() > preparing.frameCount * preparing.frameTime){
            state = E_ATTACKING;
            preparingTimer.Restart();
        }
    }

    else if(state == E_ATTACKING){
        attackingTimer.Update(dt);
        if(attackingTimer.Get() > attacking.frameCount * attacking.frameTime){
            state = E_IDLE;
            attackingTimer.Restart();
        }
    }

}

void Enemy1::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile) {
        Gravity *gravity = (Gravity*)associated.GetComponent(GRAVITY_TYPE);
        //Removes gravity after touch ground;
        if(gravity){
            state = E_IDLE;
            associated.RemoveComponent(gravity);
            onGroud = true;
        }
        associated.box.y =  other.box.y - associated.box.h;
    }

    auto player = (Player*) other.GetComponent(PLAYER_T);
    if(player){
        if(state == E_ATTACKING && !hit){
            hit = true;
            Player::player->DecrementHp();
        }
    }

}
