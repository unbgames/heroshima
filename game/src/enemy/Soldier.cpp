//
// Created by edgar on 09/07/18.
//

#include <Sprite.h>
#include <Gravity.h>
#include <Player.h>
#include <Collider.h>
#include <CollisionTile.h>
#include <Bullet.h>
#include <Sound.h>
#include <Game.h>
#include <Camera.h>
#include "Soldier.h"

Soldier::Soldier(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance) : Enemy(associated, hp,
                                                                                                         initialPosition), maxDistance(maxDistance), verticalSpeed(verticalSpeed), speed(Vec2(0,0)) {

    walking = StaticSprite("img/enemy/Soldier/soldier_walk.png", 6, 0.1f);
    attacking = StaticSprite("img/enemy/Soldier/soldier_shooting.png", 10, 0.1f);
    deadByBullet = StaticSprite("img/enemy/Soldier/soldier_deathshot.png", 7, 0.1f);
    deadBySword = StaticSprite("img/enemy/Soldier/soldier_deathsword.png", 7, 0.1f);
    idle = StaticSprite("img/enemy/Soldier/soldier_idle.png", 4, 0.1f);


    state = E_IDLE;

    Sprite* img = new Sprite(associated, idle.sprite, idle.frameCount, idle.frameTime);

    associated.orientation = LEFT;
    associated.AddComponent(img);
    associated.AddComponent(new Gravity(associated));
}

void Soldier::Update(float dt) {

    verticalSpeed += GRAVITY * dt;
    if (verticalSpeed > GRAVITY_LIMIT) {
        verticalSpeed = GRAVITY_LIMIT;
    }
    speed = Vec2(0, verticalSpeed);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    collider->box += speed;

    if(Player::player && IsCloseEnoughToPlayer(700)) {
        auto playerBox = Player::player->GetAssociatedBox();
        if(state == E_IDLE){
            idleTimer.Update(dt);
            if(idleTimer.Get() > 2){
                state = E_WALKING;
                idleTimer.Restart();
            }
        } else if (state == E_WALKING) {
            canDamage = true;
            attackCooldown.Update(dt);
            if (going) {
                if (collider->box.x < maxDistance + initialPosition.x) {
                    associated.orientation = RIGHT;
                    collider->box.x += SPEED * dt;
                } else {
                    going = false;
                }

            } else {
                if (collider->box.x > initialPosition.x) {
                    associated.orientation = LEFT;
                    collider->box.x -= SPEED * dt;
                } else going = true;
            }

            if (IsCloseEnoughToPlayer(PLAYER_DISTANCE_OFFSET)) {
                if (attackCooldown.Get() > 1)
                    state = E_ATTACKING;
            }
        } else if (state == E_ATTACKING) {
            attackingTimer.Update(dt);
            shootTimer.Update(dt);
            int shootAngle = (associated.orientation != Orientation::RIGHT ? 180 : 0);

            if(shootTimer.Get() > 0.2){
                Shoot(shootAngle);
                shootTimer.Restart();
            }
            if (attackingTimer.Get() > 1.5) {
                state = E_IDLE;
                attackCooldown.Restart();
                attackingTimer.Restart();
            }

            associated.orientation = playerBox.x < collider->box.x ? LEFT : RIGHT;
            going = associated.orientation != LEFT;
            attackingTimer.Update(dt);

        } else if (state == E_DEAD_BY_BULLET) {
            deadTimer.Update(dt);
            if (deadTimer.Get() > deadByBullet.frameCount * deadByBullet.frameTime) {
                associated.RequestDelete();
            }
        }
    }

    if (hp <= 0) {
        state = E_DEAD_BY_BULLET;
    }

    // Atualiza box com box do collider
    auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
    associated.box.x = collider->GetBox().GetCenter().x - (collider->GetBox().w / collider->GetScale().x) / 2 + offset.x;
    associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;
}

void Soldier::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if (collisionTile) {
        Gravity *gravity = (Gravity*)associated.GetComponent(GRAVITY_TYPE);
        if(gravity){
            verticalSpeed = 0;
        }
        collider->box.y = other.box.y - collider->box.h;
        auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
        associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;
    }

    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }

    auto player = (Player*)other.GetComponent(PLAYER_TYPE);
    if(player && state == E_ATTACKING && damaged){
        player->DecrementHp();
        if(player->GetHp() <= 0) state = E_WALKING;
        canDamage = false;
    }
}

void Soldier::Shoot(float angle) {
    auto bulletGo = new GameObject;
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 400, 1, 1000, "img/minionbullet2.png", 3, 0.01f, true));
    if(associated.orientation == Orientation::RIGHT){
        bulletGo->box.x = collider->box.GetPos().x + collider->box.w - bulletGo->box.w - 8;
        bulletGo->box.y = collider->box.GetPos().y + collider->box.h/2 - bulletGo->box.h + 8;
    } else {
        bulletGo->box.x = collider->box.GetPos().x + bulletGo->box.w;
        bulletGo->box.y = collider->box.GetPos().y + collider->box.h/2 - bulletGo->box.h + 8;
    }
//    auto sound(new Sound(*bulletGo, "audio/GUN SHOT.ogg"));
//    sound->Play();
//    bulletGo->AddComponent(sound);
    Game::GetInstance().GetCurrentState().AddCollisionObject(bulletGo, {1,1}, {0, -COLLISION_OFFSET * (associated.orientation == Orientation::RIGHT ? 1 : -1)});
}