//
// Created by edgar on 05/07/18.
//

#include <Collider.h>
#include <Sprite.h>
#include <SpriteSheet.h>
#include <LifeManager.h>
#include <Camera.h>
#include <Game.h>
#include <InputManager.h>
#include <CollisionTile.h>
#include <Gravity.h>
#include <PlayerArms.h>
#include "NewPlayer.h"

using std::weak_ptr;
using std::string;

NewPlayer *NewPlayer::player = nullptr;
PlayerArms *NewPlayer::playerArms = nullptr;
NewPlayer::NewPlayer(GameObject &associated) : Component(associated), hp(2), usedSecondJump(false), isDamage(false), landed(false) {

    currentSprite = SpriteSheet::idle;

    Sprite* body = new Sprite(associated, currentSprite.sprite, currentSprite.frameCount, currentSprite.frameTime);
    associated.box.w = body->GetWidth();
    associated.box.y = body->GetWidth();
    associated.AddComponent(body);
    associated.AddComponent(new Collider(associated, {0.4, 0.9}, {-8, 5}));
    player = this;

    auto pBodyGO = new GameObject;
    playerArms = new PlayerArms(*pBodyGO, Game::GetInstance().GetCurrentState().GetCollisionObjectPtr(&associated));
    pBodyGO->AddComponent(playerArms);
    Game::GetInstance().GetCurrentState().AddCollisionObject(pBodyGO);

}

NewPlayer::~NewPlayer() {
    player = nullptr;
}

void NewPlayer::Update(float dt) {
    // Logic to camera following
    if (associated.box.x > (float)GAME_WIDTH / 2) {
        Camera::Follow(&associated);
        Camera::followX = true;
    } else {
        Camera::Unfollow();
    }

    if(isDamage){

    } else {
        if (InputManager::GetInstance().IsKeyDown(S_KEY)) {
            movementState = CROUCH;
            if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
                associated.orientation = Orientation::LEFT;
            }
            if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
                associated.orientation = Orientation::RIGHT;
            }
        } else if (InputManager::GetInstance().IsKeyDown(A_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY)) {
            movementState = WALKING;
            if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
                associated.box.x -= PLAYER_SPEED * dt;
                associated.orientation = Orientation::LEFT;
            }
            if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
                associated.box.x += PLAYER_SPEED * dt;
                associated.orientation = Orientation::RIGHT;
            }
        } else {
            movementState = IDLE;
        }
    }

    // Adiciona gravidade
    verticalSpeed += Gravity::GetGravityAcc() * dt;

    if (jumpState == FALLING || jumpState == JUMPING) {
        landed = false;

        // Se começar a cair mudar de estado
        if (verticalSpeed > 0) {
            jumpState = FALLING;
        }

        if (!usedSecondJump) {
            if (InputManager::GetInstance().KeyPress(W_KEY)) {
                verticalSpeed = -1 * JUMP_SPEED * dt;
                usedSecondJump = true;
            }
        }
    } else if(jumpState == LANDING) {
        landingTimer.Update(dt);
        horizontalSpeed += (associated.orientation == RIGHT ? 50 : -50) * dt;
        if(landingTimer.Get() > currentSprite.frameTime * currentSprite.frameCount){
            landed = true;
            landingTimer.Restart();
            jumpState = ONGROUND;
        }
    } else if(jumpState == ONGROUND) {
        if (InputManager::GetInstance().KeyPress(W_KEY)) {
            verticalSpeed -= JUMP_SPEED * dt;
            jumpState = JUMPING;
            usedSecondJump = false;
        }
    }

    speed = Vec2(horizontalSpeed, verticalSpeed);
    associated.box += speed;

    // Recomeça o movimento
    horizontalSpeed = 0;

    if(hp <= 0){
        associated.RequestDelete();
    }

}

void NewPlayer::Render() {
    if(movementState == CROUCH){
        currentSprite = SpriteSheet::crouch;
    }

    if(movementState == WALKING){
        currentSprite = SpriteSheet::walking;
    }

    if(movementState == IDLE){
        currentSprite = SpriteSheet::idle;
    }

    if(jumpState == JUMPING){
        currentSprite = SpriteSheet::jumping;
    }

    if(jumpState == FALLING){
        currentSprite = SpriteSheet::falling;
    }

    if(jumpState == LANDING){
        currentSprite = SpriteSheet::landing;
    }

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    sprite->Open(currentSprite.sprite);
    sprite->SetFrameCount(currentSprite.frameCount);
    sprite->SetFrameTime(currentSprite.frameTime);
}

bool NewPlayer::Is(string type) {
    return type == PLAYER_TYPE;
}

int NewPlayer::GetHp() const {
    return hp;
}

void NewPlayer::SetHp(int hp) {
    if(hp <= PLAYER_MAX_LIVES && hp >= 0) {
        this->hp = hp;
        LifeManager::Update();
    }
}

void NewPlayer::IncremmentHp() {
    if(this->hp < PLAYER_MAX_LIVES) {
        this->hp++;
        LifeManager::Update();
    }
}

void NewPlayer::DecrementHp() {
    if(this->hp > 0) {
        this->hp--;
        LifeManager::Update();
    }
}

void NewPlayer::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if (collisionTile && collider) {
        auto edge = collider->GetEdge();
        if (edge.RIGHT) {
            horizontalSpeed = 0;
            associated.box.x =  other.box.x - associated.box.w;
        } else if (edge.LEFT) {
            horizontalSpeed = 0;
            associated.box.x =  other.box.x + other.box.w;
        } else if (edge.BOTTOM) {
            verticalSpeed = 0;
            associated.box.y =  other.box.y - associated.box.h;
            jumpState = landed ? ONGROUND : LANDING;
        }
    }
}
