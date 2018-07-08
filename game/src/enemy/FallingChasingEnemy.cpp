//
// Created by edgar on 07/06/18.
//

#include <Sprite.h>
#include <Gravity.h>
#include <CollisionTile.h>
#include <Bullet.h>
#include <Collider.h>
#include <Player.h>
#include <Sound.h>
#include <Game.h>
#include "FallingChasingEnemy.h"

FallingChasingEnemy::FallingChasingEnemy(GameObject &associated, int hp, Vec2 initialPosition, bool startFalling)
        : Enemy(associated, hp, initialPosition), fell(false), landed(false), hit(false), speed({0, 0}) {

    falling = StaticSprite("img/assassin_idel.png", 2, 0.2f);
    chasing = StaticSprite("img/assassin_andando.png", 6, 0.06f);
    idle = StaticSprite("img/assassin_idel.png", 4, 0.2f);
    stopped = StaticSprite("img/assassin_idel.png", 4, 0.2f);
    preparing = StaticSprite("img/assassin_idel.png", 4, 0.2f);
    attacking = StaticSprite("img/assassin_ataque.png", 8, 0.08f);
    deadByBullet = StaticSprite("img/assassin_deadshot.png", 7, 0.1f, 7);

    state = E_STOPPED;

    Sprite* img = new Sprite(associated, idle.sprite, idle.frameCount, idle.frameTime);

    if(startFalling){
        associated.box += {0, -3*associated.box.h};
    }

    associated.orientation = LEFT;
    associated.AddComponent(img);
}

void FallingChasingEnemy::Update(float dt) {
    if (Player::player) {
        auto playerBox = Player::player->GetAssociatedBox();

        if (state == E_STOPPED) {

            if (playerBox.x > associated.box.x - PLAYER_DISTANCE_OFFSET && !fell) {
                state = E_FALLING;
                if (!fell) {
                    fell = true;
                    associated.AddComponent(new Gravity(associated));
                }
            }

        } else if (state == E_IDLE) {

            hit = false;
            idleTimer.Update(dt);
            if (idleTimer.Get() > IDLE_TIME) {
                state = E_CHASING;
                idleTimer.Restart();
            }

        } else if (state == E_CHASING) {

            if (!IsCloseEnoughToPlayer(PLAYER_DISTANCE_THRESHOLD)) {
                if (associated.box.x > playerBox.x + PLAYER_DISTANCE_THRESHOLD) {
                    associated.orientation = LEFT;
                    associated.box.x -= SPEED * dt;
                } else if (associated.box.x < playerBox.x - PLAYER_DISTANCE_THRESHOLD + associated.box.w / 2) {
                    associated.orientation = RIGHT;
                    associated.box.x += SPEED * dt;
                }
            } else {
                state = E_PREPARING;
            }

        } else if (state == E_PREPARING) {

            preparingTimer.Update(dt);
            if (preparingTimer.Get() > preparing.frameCount * preparing.frameTime) {
                state = E_ATTACKING;
                preparingTimer.Restart();
                auto attackingGO(new GameObject);
                auto attackingSound(new Sound(*attackingGO, "audio/INIMIGO ATACANDO.ogg"));
                attackingSound->Play();
                attackingGO->AddComponent(attackingSound);
                Game::GetInstance().GetCurrentState().AddObject(attackingGO);
            }

        } else if (state == E_ATTACKING) {

            attackingTimer.Update(dt);
            if (attackingTimer.Get() > attacking.frameCount * attacking.frameTime) {
                state = E_IDLE;
                attackingTimer.Restart();
            } else if (abs(associated.box.x - playerBox.x) > 25) {
                associated.box.x += (associated.orientation == RIGHT ? 1 : -1) * SPEED * dt;
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

void FallingChasingEnemy::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile) {
        Gravity *gravity = (Gravity*)associated.GetComponent(GRAVITY_TYPE);
        if(!landed){
            state = E_IDLE;
        }
        if(gravity){
            gravity->SetVerticalSpeed(0);
            landed = true;
        }
        associated.box.y =  other.box.y - associated.box.h;
    }

    auto player = (Player*) other.GetComponent(PLAYER_TYPE);
    if(player){
        if(state == E_ATTACKING && !hit){
            hit = true;
            Player::player->DecrementHp();
        }
    }

    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);
    if(bullet && !bullet->targetsPlayer){
        hp -= bullet->GetDamage();
    }

}
