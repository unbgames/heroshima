//
// Created by edgar on 01/06/18.
//

#include <Player.h>
#include <Game.h>
#include <CameraFollower.h>
#include <PeriodicEvent.h>
#include <TimerEvent.h>
#include "LifeManager.h"

Vec2 LifeManager::offset = Vec2(0, 0);
Vec2 LifeManager::startOffset = Vec2(0, 0);
vector<weak_ptr<GameObject>> LifeManager::hearts = vector<weak_ptr<GameObject>>();
int LifeManager::lastHp = 0;

LifeManager::LifeManager(Vec2 offset) {
    LifeManager::offset = LifeManager::startOffset = offset;
    hearts.resize(PLAYER_MAX_LIVES);
    lastHp = Player::player->GetHp();
}

LifeManager::~LifeManager() {
    hearts.clear();
}

void LifeManager::Update() {
    int life = Player::player->GetHp();
    for (unsigned i = 0; i < hearts.size(); i++) {
        if (hearts[i].lock()) {
            hearts[i].lock()->RequestDelete();
        }
    }

    for (unsigned i = 0; i < life; i++) {
        auto *heartGO = new GameObject;
        heartGO->AddComponent(new Sprite(*heartGO, "img/heart.png"));

        if (i == 0) {
            offset += {GAP, TOP_MARGIN};
        } else {
            offset += {heartGO->box.w + GAP, 0};
        }
        heartGO->AddComponent(new CameraFollower(*heartGO, offset));

        if(i == life-1 && life - lastHp > 0) {
            heartGO->AddComponent(new PeriodicEvent(*heartGO, 0.1, [heartGO] {
                Sprite *sprite = (Sprite *) heartGO->GetComponent(SPRITE_TYPE);
                if(sprite) sprite->SetVisible(!sprite->IsVisible());
            }));
            heartGO->AddComponent(new TimerEvent(*heartGO, 1, [heartGO]{
                PeriodicEvent *periodicEvent = (PeriodicEvent *) heartGO->GetComponent(PERIODIC_EVENT_TYPE);
                if(periodicEvent) heartGO->RemoveComponent(periodicEvent);
                Sprite *sprite = (Sprite *) heartGO->GetComponent(SPRITE_TYPE);
                if(sprite) sprite->SetVisible(true);
            }));
        }

        hearts[i] = (Game::GetInstance().GetCurrentState().AddObject(heartGO));
    }
    offset = startOffset;
    lastHp = Player::player->GetHp();
}
