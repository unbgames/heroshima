//
// Created by edgar on 01/06/18.
//

#include <Player.h>
#include <Game.h>
#include <CameraFollower.h>
#include "LifeManager.h"

LifeManager::LifeManager(GameObject &associated, Vec2 offset) : Component(associated), offset(offset) {
    hearts.resize((unsigned)(Player::player->GetHp()));
}

LifeManager::~LifeManager() {
    hearts.clear();
}

void LifeManager::Start() {
    for(unsigned i = 0; i < hearts.size(); i++){
        auto *heartGO = new GameObject;
        heartGO->AddComponent(new Sprite(*heartGO, "img/heart.png"));

        if(i == 0){
            offset += { GAP, MARGIN_TOP};
        } else{
            offset += {heartGO->box.w + GAP, 0};
        }
        heartGO->AddComponent(new CameraFollower(*heartGO, offset));

        hearts[i] = (Game::GetInstance().GetCurrentState().AddObject(heartGO));
    }
}

void LifeManager::Update(float dt) {

}

void LifeManager::Render() {}

bool LifeManager::Is(string type) {
    return type == LIFE_MANAGER_TYPE;
}
