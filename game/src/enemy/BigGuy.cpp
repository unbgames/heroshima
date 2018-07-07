//
// Created by edgar on 04/07/18.
//

#include <Gravity.h>
#include <Sprite.h>
#include <Bullet.h>
#include <CollisionTile.h>
#include <Camera.h>
#include <Player.h>
#include "BigGuy.h"

BigGuy::BigGuy(GameObject &associated, int hp, const Vec2 &initialPosition, float maxDistance) : Enemy(associated, hp, initialPosition),
                                                                                                 going(true), initialPosition(initialPosition),
                                                                                                 maxDistance(maxDistance) {

    walking = StaticSprite("img/enemy/BigGuy/walking.png", 6, 0.1f);
    attacking = StaticSprite("img/enemy/BigGuy/attack.png", 9, 0.1f);
    deadByBullet = StaticSprite("img/enemy/BigGuy/death.png", 5, 0.1f);

    state = E_WALKING;

    Sprite* img = new Sprite(associated, walking.sprite, walking.frameCount, walking.frameTime);

    associated.orientation = RIGHT;
    associated.AddComponent(img);
    associated.AddComponent(new Gravity(associated));
}

void BigGuy::Update(float dt) {
    if(Player::player) {
        auto playerBox = Player::player->GetAssociatedBox();

        if (state == E_WALKING) {
            attackCooldown.Update(dt);
            if (going) {
                if (associated.box.x < maxDistance + initialPosition.x) {
                    associated.orientation = RIGHT;
                    associated.box.x += SPEED * dt;
                } else {
                    going = false;
                }

            } else {
                if (associated.box.x > initialPosition.x) {
                    associated.orientation = LEFT;
                    associated.box.x -= SPEED * dt;
                } else going = true;
            }

            if (IsCloseEnoughToPlayer(PLAYER_DISTANCE_OFFSET)) {
                if (attackCooldown.Get() > 3)
                    state = E_ATTACKING;
            }
        } else if (state == E_ATTACKING) {
            associated.orientation = playerBox.x < associated.box.x ? LEFT : RIGHT;
            going = associated.orientation != LEFT;
            attackingTimer.Update(dt);

            if (attackingTimer.Get() > (attacking.frameCount * attacking.frameTime) * (5.0F / 9.0F)) {
                Camera::Wiggle(0.2);
            }
            if (attackingTimer.Get() > attacking.frameCount * attacking.frameTime) {
                state = E_WALKING;
                attackCooldown.Restart();
                attackingTimer.Restart();
            }
        } else if (state == E_DEAD_BY_BULLET) {
            deadTimer.Update(dt);
            if (deadTimer.Get() > deadByBullet.frameCount * deadByBullet.frameTime) {
                associated.RequestDelete();
            }
        }

        if (hp <= 0) {
            state = E_DEAD_BY_BULLET;
        }
    }
}

void BigGuy::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile) {
        Gravity *gravity = (Gravity*)associated.GetComponent(GRAVITY_TYPE);
        if(gravity){
            gravity->SetVerticalSpeed(0);
        }
        associated.box.y =  other.box.y - associated.box.h;
    }

    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }
}
