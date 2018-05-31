#include <iostream>
#include <memory>
#include <string>

#include "InputManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "PlayerBody.h"
#include "Game.h"
#include "Component.h"
#include "CollisionTile.h"
#include "Sprite.h"
#include "Player.h"

using std::weak_ptr;
using std::string;

Player *Player::player = nullptr;
PlayerBody *Player::playerBody = nullptr;
Player::Player(GameObject &associated) : Component(associated), hp(1) {

    associated.AddComponent(new Collider(associated));
    Sprite* img = new Sprite(associated, "img/tarma_inferior_repouso.png");
    associated.box.w = img->GetWidth();
    associated.box.y = img->GetWidth();
    associated.AddComponent(img);

    player = this;
}

Player::~Player() {
    player = nullptr;
}

void Player::Start() {
    jumpState = FALLING;
    movementState = RESTING;

    auto pBodyGO = new GameObject;
    playerBody = new PlayerBody(*pBodyGO, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    pBodyGO->AddComponent(playerBody);
    pBody = Game::GetInstance().GetCurrentState().AddObject(pBodyGO);

}

void Player::Update(float dt) {

    GameObject &bodyGO = *pBody.lock();
    if (bodyGO.IsDead()) {
        associated.RequestDelete();
    }

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (InputManager::GetInstance().IsKeyDown(A_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY)) {

        // Atualiza a animação
        movementState = WALKING;
        sprite->Open("img/tarma_inferior_andando.png");
        associated.box.w = sprite->GetWidth();
        associated.box.h = sprite->GetHeight();
        sprite->SetFrameCount(8);
        sprite->SetFrameTime(0.06f);

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

        // Atualiza a animação
        sprite->Open("img/tarma_inferior_repouso.png");
        associated.box.w = sprite->GetWidth();
        associated.box.h = sprite->GetHeight();
        sprite->SetFrameCount(1);
        sprite->SetFrameTime(0);
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
}

void Player::Render() {


}

bool Player::Is(string type) {
    return PLAYER_T == type;
}

void Player::NotifyCollision(GameObject &other) {
    auto collisionTile = (CollisionTile*) other.GetComponent(COLLISION_TILE_T);
    if (collisionTile != nullptr && jumpState == FALLING) {
        horizontalSpeed = 0;
        associated.box.y =  other.box.y - associated.box.h;
        jumpState = COLLIDING;
    }
}

int Player::GetHp() const {
    return hp;
}

void Player::SetHp(int hp) {
    this->hp = hp;
}

void Player::IncremmentHp() {
    this->hp++;
}

void Player::DecrementHp() {
    this->hp--;
}
