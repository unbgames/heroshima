//
// Created by edgar on 01/06/18.
//

#include <Sprite.h>
#include <CameraFollower.h>
#include <Game.h>
#include <Player.h>
#include <MenuHUD.h>
#include <LifeManager.h>
#include <SpriteSheet.h>
#include "GunManager.h"

GunManager::GunManager(GameObject &associated, Vec2 offset) : Component(associated), offset(offset) {
    gunIconGO = new GameObject();
    gunIconGO->AddComponent(new Sprite(*gunIconGO, "img/pistol_icon.png"));
    gunIconGO->AddComponent(new CameraFollower(*gunIconGO, offset - Vec2(gunIconGO->box.w, 0)));
    Game::GetInstance().GetCurrentState().AddObject(gunIconGO);

    ammoCounterGO = new GameObject();
    ammoCounterGO->AddComponent(new Text(*ammoCounterGO, "font/Japanese.ttf", 60,
                                         Text::TextStyle::BLENDED, "bla", {255, 255, 255, 255}));
    ammoCounterGO->AddComponent(new CameraFollower(*ammoCounterGO, offset - Vec2(gunIconGO->box.w + ammoCounterGO->box.w + GAP, -gunIconGO->box.h + ammoCounterGO->box.h)));
    Game::GetInstance().GetCurrentState().AddObject(ammoCounterGO);
}

void GunManager::Update(float dt) {
    auto sprite = (Sprite*)gunIconGO->GetComponent(SPRITE_TYPE);
    auto text = (Text*)ammoCounterGO->GetComponent(TEXT_TYPE);

    if(Player::playerArms->GetGun() == SpriteSheet::pistol){
        if(sprite) sprite->Open("img/pistol_icon.png");
    } else if(Player::playerArms->GetGun() == SpriteSheet::heavy){
        if(sprite) sprite->Open("img/heavy_machinegun_icon.PNG");
    }

    if(text) {
        int ammo = Player::playerArms->GetGun()->getAmmo();
        text->SetText(ammo != -1 ? to_string(ammo) : "INF");
//        cameraFollower->SetOffset(offset - Vec2(gunIconGO->box.w + ammoCounterGO->box.w + GAP, -gunIconGO->box.h + ammoCounterGO->box.h));
    }
}

void GunManager::Render() {}

bool GunManager::Is(string type) {
    return false;
}
