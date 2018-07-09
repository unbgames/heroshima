//
// Created by edgar on 05/07/18.
//

#include <cmath>

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
#include <SwordThreshold.h>
#include "Player.h"

using std::weak_ptr;
using std::string;

Player *Player::player = nullptr;
PlayerArms *Player::playerArms = nullptr;
Player::Player(GameObject &associated) : Component(associated), hp(2), usedSecondJump(false), isDamage(false), landed(false), movementState(IDLE), jumpState(ONGROUND), transformed(false), horizontalSpeed(0.0), verticalSpeed(0.0) {

    currentSprite = SpriteSheet::transformation;

    Sprite* body = new Sprite(associated, currentSprite.sprite, currentSprite.frameCount, currentSprite.frameTime);
    associated.box.w = body->GetWidth();
    associated.box.y = body->GetWidth();
    associated.AddComponent(body);
    associated.AddComponent(new Collider(associated));
    player = this;

}

void Player::Start() {
    auto arms = new GameObject;
    playerArms = new PlayerArms(*arms, Game::GetInstance().GetCurrentState().GetCollisionObjectPtr(&associated));
    arms->AddComponent(playerArms);
    Game::GetInstance().GetCurrentState().AddCollisionObject(arms);
}

Player::~Player() {
    player = nullptr;
}

void Player::Update(float dt) {

    // Logic to camera following
    if (associated.box.x < -30) {
        movementState = BLOCKED_LEFT;
    } else if (associated.box.x > (float)GAME_WIDTH / 2 + 10) {
        Camera::Follow(&associated);
        Camera::followX = true;
    } else {
        Camera::Unfollow();
    }

    //To test the life indicator
    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))DecrementHp();
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))IncremmentHp();
    //Remove

    //To test wiggle effect
    if(InputManager::GetInstance().IsKeyDown(ENTER_KEY))Camera::Wiggle(0.5);
    //Remove

    // Adiciona gravidade
    verticalSpeed += Gravity::GetGravityAcc() * dt;

    if (!transformed) {

        transformationTimer.Update(dt);
        if(transformationTimer.Get() > currentSprite.frameTime * currentSprite.frameCount){
            transformed = true;
            jumpState = ONGROUND;
        }

    } else if (isDamage) {

    } else {

        auto sprite = (Sprite *) associated.GetComponent(SPRITE_TYPE);
        if (InputManager::GetInstance().IsKeyDown(S_KEY)) {

            movementState = CROUCH;
            if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
                associated.orientation = Orientation::LEFT;
            }

            if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
                associated.orientation = Orientation::RIGHT;
            }

        } else if (InputManager::GetInstance().IsKeyDown(A_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY)) {

            if (InputManager::GetInstance().IsKeyDown(A_KEY)) {

                if (movementState != BLOCKED_LEFT) {
                    associated.box.x -= ((0.35 * abs(cos((sprite->GetCurrentFrame() + 1) * (M_PI / 4)))) + 0.65) * PLAYER_SPEED * dt;
                    movementState = WALKING;
                }
                associated.orientation = Orientation::LEFT;

            }
            if (InputManager::GetInstance().IsKeyDown(D_KEY)) {

                if (movementState != BLOCKED_RIGHT) {
                    associated.box.x += ((0.35 * abs(cos((sprite->GetCurrentFrame() + 1) * (M_PI / 4)))) + 0.65) * PLAYER_SPEED * dt;
                    movementState = WALKING;
                }
                associated.orientation = Orientation::RIGHT;

            }
        } else {
            movementState = IDLE;
        }

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

        } else if (jumpState == LANDING) {

            landingTimer.Update(dt);
            horizontalSpeed += (associated.orientation == RIGHT ? 50 : -50) * dt;
            if (landingTimer.Get() > currentSprite.frameTime * currentSprite.frameCount) {
                landed = true;
                landingTimer.Restart();
                jumpState = ONGROUND;
            }

        } else if (jumpState == ONGROUND) {

            if (InputManager::GetInstance().KeyPress(W_KEY)) {
                verticalSpeed -= (Gravity::GetGravityAcc() + JUMP_SPEED) * dt;
                jumpState = JUMPING;
                usedSecondJump = false;
            }
        }

//        if(IsAttacking() && useSword){
//            movementState = SWORD_ATTACK;
//            swordTimer.Update(dt);
//
//            if(swordTimer.Get() > currentSprite.frameCount * currentSprite.frameTime){
//                movementState = IDLE;
//                swordTimer.Restart();
//            }
//        }

//        cout<<(useSword ? "true" : "false") <<endl;
    }

    speed = Vec2(horizontalSpeed, verticalSpeed);
    associated.box += speed;

    // Force update from collider
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    collider->Update(dt);

    // Recomeça o movimento
    horizontalSpeed = 0;

    if (hp <= 0) {
        associated.RequestDelete();
        Camera::Unfollow();
    }

}

void Player::Render() {

    if (!transformed) {

        currentSprite = SpriteSheet::transformation;

    } else {

        if (movementState == CROUCH) {
            currentSprite = SpriteSheet::crouch;
        }

        if (movementState == WALKING || movementState == BLOCKED_LEFT || movementState == BLOCKED_RIGHT) {
            currentSprite = SpriteSheet::walking;
        }

        if (movementState == IDLE) {
            currentSprite = SpriteSheet::idle;
        }

        if (jumpState == JUMPING) {
            currentSprite = SpriteSheet::jumping;
        }

        if (jumpState == FALLING) {
            currentSprite = SpriteSheet::falling;
        }

        if (jumpState == LANDING) {
            currentSprite = SpriteSheet::landing;
        }

//        if(movementState == SWORD_ATTACK){
//            int random = rand() % 3;
//            if(random == 0) currentSprite = SpriteSheet::sword1;
//            else if(random == 1) currentSprite = SpriteSheet::sword2;
//            else  currentSprite = SpriteSheet::sword3;
//        }
    }

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    sprite->Open(currentSprite.sprite);
    sprite->SetFrameCount(currentSprite.frameCount);
    sprite->SetFrameTime(currentSprite.frameTime);
}

bool Player::Is(string type) {
    return type == PLAYER_TYPE;
}

int Player::GetHp() const {
    return hp;
}

void Player::SetHp(int hp) {
    if(hp <= PLAYER_MAX_LIVES && hp >= 0) {
        this->hp = hp;
        LifeManager::Update();
    }
}

void Player::IncremmentHp() {
    if(this->hp < PLAYER_MAX_LIVES) {
        this->hp++;
        LifeManager::Update();
    }
}

void Player::DecrementHp() {
    if(this->hp > 0) {
        this->hp--;
        LifeManager::Update();
    }
}

void Player::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if (collisionTile && collider) {
        auto edge = collider->GetEdge();

        if (edge.BOTTOM) {
            verticalSpeed = 0;
            associated.box.y = other.box.y - associated.box.h + 1;
            jumpState = landed ? ONGROUND : LANDING;
        }

//        else if (edge.RIGHT) {
//            movementState = BLOCKED_RIGHT;
//            horizontalSpeed = 0;
//            associated.box.x = other.box.x - associated.box.w;
//        } else if (edge.LEFT) {
//            movementState = BLOCKED_LEFT;
//            horizontalSpeed = 0;
//            associated.box.x = other.box.x;
//        }


    }

        auto swordTrigger = (SwordThreshold *) other.GetComponent(SWORD_THRESHOLD_TYPE);
        if (swordTrigger) {
            useSword = true;
        } else {
            useSword = false;
        }
}

bool Player::IsTransformed() const {
    return transformed;
}

bool Player::IsAttacking() const {
    return playerArms->IsAttacking();
}

MoveState Player::getMovementState() {
    return movementState;
}

JumpState Player::getJumpState() {
    return jumpState;
}

bool Player::UseSword() const {
    return useSword;
}
