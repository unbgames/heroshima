#include <iostream>
#include <memory>
#include <LifeManager.h>
#include <SpriteSheet.h>
#include <PeriodicEvent.h>
#include <TimerEvent.h>

#include "InputManager.h"
#include "Collider.h"
#include "PlayerArms.h"
#include "Game.h"
#include "CollisionTile.h"
#include "Sprite.h"
#include "Player.h"

using std::weak_ptr;
using std::string;

Player *Player::player = nullptr;
PlayerArms *Player::playerArms = nullptr;
Player::Player(GameObject &associated) : Component(associated), hp(2) {

    bodyState = SpriteSheet::idle;

    Sprite* img = new Sprite(associated, bodyState->GetCurrent().sprite, bodyState->GetCurrent().frameCount, bodyState->GetCurrent().frameTime);
    associated.box.w = img->GetWidth();
    associated.box.y = img->GetWidth();
    associated.AddComponent(img);
    associated.AddComponent(new Collider(associated, {0.4, 0.9}, {-8, 5}));

    player = this;
}

Player::~Player() {
    player = nullptr;
}

void Player::Start() {
    jumpState = FALLING;
    movementState = RESTING;

    auto pBodyGO = new GameObject;
    playerArms = new PlayerArms(*pBodyGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    pBodyGO->AddComponent(playerArms);
    Game::GetInstance().GetCurrentState().AddObject(pBodyGO);

}

void Player::Update(float dt) {

    //To test the life indicator
    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))DecrementHp();
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))IncremmentHp();
    //Remove

    if (InputManager::GetInstance().IsKeyDown(A_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY)) {
        movementState = WALKING;
        bodyState = SpriteSheet::walking;

        if (InputManager::GetInstance().IsKeyDown(A_KEY)){
            associated.box.x -= PLAYER_SPEED * dt;
            associated.orientation = Orientation::LEFT;
        }
        if (InputManager::GetInstance().IsKeyDown(D_KEY)){
            associated.box.x += PLAYER_SPEED * dt;
            associated.orientation = Orientation::RIGHT;
        }
    } else {
        movementState = RESTING;
        bodyState = SpriteSheet::idle;
    }

    if (jumpState == JUMPING || jumpState == FALLING) {

        // Adiciona gravidade
        horizontalSpeed += GRAVITY * dt;

        // Se começar a cair mudar de estado
        if (horizontalSpeed > 0) jumpState = FALLING;

    } else {

        if (InputManager::GetInstance().KeyPress(W_KEY)) {
            horizontalSpeed -= JUMP_SPEED * dt;
            jumpState = JUMPING;
        } else {
            jumpState = FALLING;
        }
    }

    speed = Vec2(verticalSpeed, horizontalSpeed);
    associated.box += speed;

    // Recomeça o movimento
    verticalSpeed = 0;

    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Player::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    sprite->Open(bodyState->GetCurrent().sprite);
    sprite->SetFrameCount(bodyState->GetCurrent().frameCount);
    sprite->SetFrameTime(bodyState->GetCurrent().frameTime);
}

bool Player::Is(string type) {
    return PLAYER_T == type;
}

void Player::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    auto collider = (Collider*) associated.GetComponent(COLLIDER_TYPE);
    if (collisionTile && collider) {
        auto edge = collider->GetEdge();
        if (edge.RIGHT) {
            verticalSpeed = 0;
            associated.box.x =  other.box.x - associated.box.w;
        } else if (edge.LEFT) {
            verticalSpeed = 0;
            associated.box.x =  other.box.x + other.box.w;
        } else if (edge.BOTTOM) {
            horizontalSpeed = 0;
            associated.box.y =  other.box.y - associated.box.h;
            jumpState = ONGROUND;
        }
    }
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

MoveState Player::getMovementState() const {
    return movementState;
}
