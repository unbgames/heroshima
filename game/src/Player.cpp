//
// Created by edgar on 17/05/18.
//

#include <Collider.h>
#include <InputManager.h>
#include <Camera.h>
#include "Player.h"

Player *Player::player = nullptr;

Player::Player(GameObject &associated) : Component(associated), speed(0, 0), linearSpeed(0), angle(0), hp(100), andando(false), direita(true), estavaAndando(false) {
    associated.AddComponent(new Collider(associated));
    associated.AddComponent(new Sprite(associated, "img/spritesheet_kays_parado.png", 3, 0.3));
    player = this;
}

Player::~Player() {
    player = nullptr;
}

void Player::Start() {
    Component::Start();
}

void Player::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    estavaAndando = andando;

    if (inputManager.IsKeyDown(A_KEY) || inputManager.IsKeyDown(D_KEY)){
        andando = true;
        if (inputManager.IsKeyDown(A_KEY)){
            linearSpeed -= PLAYER_SPEED * dt;
            direita = false;
        }
        if (inputManager.IsKeyDown(D_KEY)){
            linearSpeed += PLAYER_SPEED * dt;
            direita = true;
        }
    } else{
        andando = false;
    }

    associated.angleDeg = angle;
    speed = Vec2(linearSpeed , 0);//.RotateDeg(angle);
    associated.box += speed;

    if(hp <= 0){
        associated.RequestDelete();
        Camera::Unfollow();
    }
}

void Player::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if(!estavaAndando && andando){
        sprite->Open("img/spritesheet_kays_andando.png");
        sprite->SetFrameCount( 4 );
        sprite->SetFrameTime(0.2);

    } else if(estavaAndando && !andando){
        sprite->Open("img/spritesheet_kays_parado.png");
        sprite->SetFrameCount( 3 );
        sprite->SetFrameTime(0.3);
    }
    sprite->SetFlip(!direita);
}

bool Player::Is(string type) {
    return false;
}

void Player::NotifyCollision(GameObject &other) {
    Component::NotifyCollision(other);
}
