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
#include <Sound.h>
#include <TitleState.h>
#include "Player.h"

using std::weak_ptr;
using std::string;

Player *Player::player = nullptr;
PlayerArms *Player::playerArms = nullptr;
Player::Player(GameObject &associated) : Component(associated), hp(2), usedSecondJump(false), landed(false), movementState(IDLE), jumpState(ONGROUND), horizontalSpeed(0.0), verticalSpeed(0.0), playedDeathSound(false) {

    currentSprite = SpriteSheet::soldier;
    bodyState = INITIAL;

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
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);

    // Logic to camera following
    if (collider->box.x < 10) {
        movementState = BLOCKED_LEFT;
    } else if (collider->box.x > 11600) {
        Camera::Unfollow();
    } else if (collider->box.x > 11800) {
        movementState = BLOCKED_RIGHT;
    } else if (collider->box.x > (float)GAME_WIDTH / 2 + 50) {
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

    if (bodyState == INITIAL) {
        if (InputManager::GetInstance().IsKeyDown(A_KEY) ||
            InputManager::GetInstance().IsKeyDown(D_KEY) ||
            InputManager::GetInstance().IsKeyDown(W_KEY) ||
            InputManager::GetInstance().IsKeyDown(S_KEY)) {
            bodyState = TRANSFORMING;
            auto transformGO(new GameObject);
            auto transformSound(new Sound(*transformGO, "audio/TRANSFORMAÇÃO.ogg"));
            transformSound->Play();
            transformGO->AddComponent(transformSound);
            Game::GetInstance().GetCurrentState().AddObject(transformGO);
        }
    } else if (bodyState == TRANSFORMING) {

        transformationTimer.Update(dt);
        if(transformationTimer.Get() > currentSprite.frameTime * currentSprite.frameCount){
            bodyState = DEFAULT;
            jumpState = ONGROUND;
        }

    } else if (bodyState == DAMAGED) {

    } else if (bodyState == DEATH) {

        deadTimer.Update(dt);
        if (deadTimer.Get() > currentSprite.frameCount * currentSprite.frameTime) {
            Camera::Unfollow();
            Camera::pos = {0,0};
            associated.RequestDelete();
            Game::GetInstance().Push(new TitleState());
        }

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
                    collider->box.x -= ((0.35f * (float)abs(cos((sprite->GetCurrentFrame() + 1) * (M_PI / 4)))) + 0.65f) * (float)PLAYER_SPEED * dt;
                    movementState = WALKING;
                }
                associated.orientation = Orientation::LEFT;

            }
            if (InputManager::GetInstance().IsKeyDown(D_KEY)) {

                if (movementState != BLOCKED_RIGHT) {
                    collider->box.x += ((0.35f * (float)abs(cos((sprite->GetCurrentFrame() + 1) * (M_PI / 4)))) + 0.65f) * (float)PLAYER_SPEED * dt;
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
                            auto jumpGO(new GameObject);
                            auto jumpSound(new Sound(*jumpGO, "audio/SALTO.ogg"));
                            jumpSound->Play();
                            jumpGO->AddComponent(jumpSound);
                            Game::GetInstance().GetCurrentState().AddObject(jumpGO);
                        }
                    }

        } else if (jumpState == LANDING) {

            landingTimer.Update(dt);
            horizontalSpeed += (associated.orientation == RIGHT ? 50 : -50) * dt;
            if (landingTimer.Get() > currentSprite.frameTime * currentSprite.frameCount) {
                landed = true;
                landingTimer.Restart();
                jumpState = ONGROUND;
                auto landingGO(new GameObject);
                auto landingSound(new Sound(*landingGO, "audio/ATERRISSAGEM.ogg"));
                landingSound->Play();
                landingGO->AddComponent(landingSound);
                Game::GetInstance().GetCurrentState().AddObject(landingGO);
            }

        } else if (jumpState == ONGROUND) {

            if (InputManager::GetInstance().KeyPress(W_KEY)) {
                verticalSpeed -= (Gravity::GetGravityAcc() + JUMP_SPEED) * dt;
                jumpState = JUMPING;
                usedSecondJump = false;
                auto jumpGO(new GameObject);
                auto jumpSound(new Sound(*jumpGO, "audio/SALTO.ogg"));
                jumpSound->Play();
                jumpGO->AddComponent(jumpSound);
                Game::GetInstance().GetCurrentState().AddObject(jumpGO);
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
    collider->box += speed;

    // Atualiza box com box do collider
    auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
    associated.box.x = collider->GetBox().GetCenter().x - (collider->GetBox().w / collider->GetScale().x) / 2 + offset.x;
    associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;

    // Recomeça o movimento
    horizontalSpeed = 0;

    if (hp <= 0) {
        bodyState = DEATH;

        if (!playedDeathSound) {
            auto dyingGO(new GameObject);
            auto dyingSound(new Sound(*dyingGO, "audio/MORTEHERO.ogg"));
            dyingSound->Play();
            dyingGO->AddComponent(dyingSound);
            Game::GetInstance().GetCurrentState().AddObject(dyingGO);
            playedDeathSound = true;
        }
    }

}

void Player::Render() {

    if (bodyState == INITIAL) {
        currentSprite = SpriteSheet::soldier;
    } else if (bodyState == TRANSFORMING) {
        currentSprite = SpriteSheet::transformation;
    } else if (bodyState == DEATH) {
        currentSprite = SpriteSheet::death;
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
            collider->box.y = other.box.y - collider->box.h + 1;
            auto offset = (Vec2(0,0)-collider->GetOffset()).RotateDeg((float)(associated.angleDeg));
            associated.box.y = collider->GetBox().GetCenter().y - (collider->GetBox().h / collider->GetScale().y) / 2 + offset.y;
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

BodyState Player::GetBodyState() const {
    return bodyState;
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
