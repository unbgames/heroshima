#include <string>
#include <memory>

#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Player.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Component.h"
#include "PlayerBody.h"

using std::string;
using std::weak_ptr;


PlayerBody::PlayerBody(GameObject &associated, weak_ptr<GameObject> player)
    : Component(associated) {

    this->player = player;
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.AddComponent(new Collider(associated));
    Sprite* img = new Sprite(associated, "img/tarma_superior_repouso.png", 4, 0.5f);
    associated.orientation = playerGO.orientation;
    associated.box.x = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL + playerGO.box.GetCenter().x - img->GetWidth() / 2;
    associated.box.y = BODY_OFFSET_VERTICAL + playerGO.box.y - img->GetHeight();
    associated.box.w = img->GetWidth();
    associated.box.h = img->GetHeight();
    associated.AddComponent(img);
}

void PlayerBody::Start() {
}

void PlayerBody::Update(float dt) {
    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.box.x = offset + playerGO.box.GetCenter().x - associated.box.w / 2;
    associated.box.y = BODY_OFFSET_VERTICAL + playerGO.box.y - associated.box.h;
    associated.orientation = playerGO.orientation;

    if (InputManager::GetInstance().IsKeyDown(SPACE_BAR_KEY)) {
        state = SHOOTING;
        int shootAngle = (playerGO.orientation == GameObject::LEFT ? 180 : 0);
        Shoot(shootAngle);
        offset = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_SHOOT;

    } else {
        state = RESTING;
        offset = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL;
    }
}

void PlayerBody::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (state == SHOOTING) {
        sprite->Open("img/tarma_superior_atirando.png");
        sprite->SetFrameCount(10);
        sprite->SetFrameTime(0.5f);

    } else if (state == RESTING) {
        sprite->Open("img/tarma_superior_repouso.png");
        sprite->SetFrameCount(4);
        sprite->SetFrameTime(1);
    }
}

bool PlayerBody::Is(string type) {
    return type == PLAYER_BODY_T;
}

void PlayerBody::Shoot(float angle) {
    auto bulletGo = new GameObject;
    if(associated.orientation == GameObject::RIGHT){
        bulletGo->box.x = associated.box.GetPos().x + associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 + bulletGo->box.h - 7;
    } else {
        bulletGo->box.x = associated.box.GetPos().x - associated.box.w + bulletGo->box.w;
        bulletGo->box.y = associated.box.GetPos().y + associated.box.h/2 - bulletGo->box.h - 7;
    }
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 700, 20, 1000, "img/minionbullet2.png", 3, 0.01, true));
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}
