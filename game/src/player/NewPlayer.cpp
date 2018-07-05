//
// Created by edgar on 05/07/18.
//

#include <Collider.h>
#include <Sprite.h>
#include <SpriteSheet.h>
#include <LifeManager.h>
#include "NewPlayer.h"

using std::weak_ptr;
using std::string;

NewPlayer *NewPlayer::player = nullptr;
NewPlayer::NewPlayer(GameObject &associated) : Component(associated), hp(2), usedSecondJump(false) {

    currentSprite = SpriteSheet::idle;

    Sprite* img = new Sprite(associated, currentSprite.sprite, currentSprite.frameCount, currentSprite.frameTime);
    associated.box.w = img->GetWidth();
    associated.box.y = img->GetWidth();
    associated.AddComponent(img);
    associated.AddComponent(new Collider(associated, {0.4, 0.9}, {-8, 5}));

    player = this;
}

NewPlayer::~NewPlayer() {
    player = nullptr;
}

void NewPlayer::Update(float dt) {

}

void NewPlayer::Render() {

}

bool NewPlayer::Is(string type) {
    return type == PLAYER_TYPE;
}

int NewPlayer::GetHp() const {
    return hp;
}

void NewPlayer::SetHp(int hp) {
    if(hp <= PLAYER_MAX_LIVES && hp >= 0) {
        this->hp = hp;
        LifeManager::Update();
    }
}

void NewPlayer::IncremmentHp() {
    if(this->hp < PLAYER_MAX_LIVES) {
        this->hp++;
        LifeManager::Update();
    }
}

void NewPlayer::DecrementHp() {
    if(this->hp > 0) {
        this->hp--;
        LifeManager::Update();
    }
}