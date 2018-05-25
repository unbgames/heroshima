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
Player::Player(GameObject &associated)
        : Component(associated) {

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
    pBodyGO->AddComponent(new PlayerBody(*pBodyGO,
        Game::GetInstance().GetCurrentState().GetObjectPtr(&associated)));
    pBody = Game::GetInstance().GetCurrentState().AddObject(pBodyGO);

}

void Player::Update(float dt) {

    GameObject &bodyGO = *pBody.lock();
    if (bodyGO.IsDead()) {
        associated.RequestDelete();
    }

    if (InputManager::GetInstance().IsKeyDown(A_KEY) || InputManager::GetInstance().IsKeyDown(D_KEY)) {
        movementState = WALKING;
        if (InputManager::GetInstance().IsKeyDown(A_KEY)){
            associated.box.x -= PLAYER_SPEED * dt;
            associated.orientation = GameObject::LEFT;
        }
        if (InputManager::GetInstance().IsKeyDown(D_KEY)){
            associated.box.x += PLAYER_SPEED * dt;
            associated.orientation = GameObject::RIGHT;
        }
    } else {
        movementState = RESTING;
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

    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (movementState == WALKING) {
        sprite->Open("img/tarma_inferior_andando.png");
        sprite->SetFrameCount(12);
        sprite->SetFrameTime(0.5);
        cout << sprite->GetCurrentFrame()<<endl;

    } else if (movementState == RESTING) {
        sprite->Open("img/tarma_inferior_repouso.png");
        sprite->SetFrameCount(1);
        sprite->SetFrameTime(0);
    }
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