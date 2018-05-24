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
    Sprite* img = new Sprite(associated, "img/tarma_superior_repouso.png", 4, 0.2f);
    associated.orientation = playerGO.orientation;
    associated.box.x = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL + playerGO.box.GetCenter().x - img->GetWidth() / 2;
    associated.box.y = BODY_OFFSET_VERTICAL + playerGO.box.y - img->GetHeight();
    associated.box.w = img->GetWidth();
    associated.box.h = img->GetHeight();
    associated.AddComponent(img);
}

void PlayerBody::Start() {
    Component::Start();
}

void PlayerBody::Update(float dt) {

    GameObject &playerGO = *player.lock();
    if (playerGO.IsDead()) {
        associated.RequestDelete();
    }

    associated.orientation = playerGO.orientation;
    int offset = (playerGO.orientation == GameObject::LEFT ? -1 : 1) * BODY_OFFSET_HORIZONTAL;

    associated.box.x = offset + playerGO.box.GetCenter().x - associated.box.w / 2;
    associated.box.y = BODY_OFFSET_VERTICAL + playerGO.box.y - associated.box.h;

    if (InputManager::GetInstance().IsKeyDown(SPACE_BAR_KEY)) {
        state = SHOOTING;
        int shootAngle = (playerGO.orientation == GameObject::LEFT ? 180 : 0);
        Shoot(shootAngle);

    } else {
        state = RESTING;
    }
}

void PlayerBody::Render() {
    auto sprite = (Sprite*)associated.GetComponent(SPRITE_TYPE);
    if (state == SHOOTING) {
        sprite->Open("img/tarma_superior_atirando.png");
        sprite->SetFrameCount(10);
        sprite->SetFrameTime(0.5);

    } else if (state == RESTING) {
        sprite->Open("img/tarma_superior_repouso.png");
        sprite->SetFrameCount(4);
        sprite->SetFrameTime(0.2);
    }
}

bool PlayerBody::Is(string type) {
    return false;
}

void PlayerBody::Shoot(float angle) {
    auto bulletGo = new GameObject;
    bulletGo->box.x = associated.box.GetCenter().x - bulletGo->box.w / 2;
    bulletGo->box.y = associated.box.GetCenter().y - bulletGo->box.h / 2;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 300, 20, 1000, "img/minionbullet2.png", 3, 0.01, true));
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}
