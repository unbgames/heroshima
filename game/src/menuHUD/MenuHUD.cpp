//
// Created by edgar on 31/05/18.
//

#include <engine/Game.h>
#include <engine/components/CameraFollower.h>
#include <engine/components/Sprite.h>
#include <menuHUD/LifeManager.h>
#include <menuHUD/GunManager.h>
#include "menuHUD/MenuHUD.h"

MenuHUD::MenuHUD(GameObject &associated, bool isFace, bool isLifeIndicator, bool isClock) :
        Component(associated), isClock(isClock), isFace(isFace) {
    if(isFace){
        AddFace();
    }

    if(isLifeIndicator){
        AddLifeIndicator();
    }

    if(isClock){
        AddClock();
    }

    auto gunIcon(new GameObject());
    gunIcon->AddComponent(new GunManager(*gunIcon, {GAME_WIDTH - gunIcon->box.w - MARGIN_LEFT, MARGIN_TOP}));
    Game::GetInstance().GetCurrentState().AddObject(gunIcon);


}

void MenuHUD::Update(float dt) {
    if(isClock) {
        clock->Update(dt);
        Text *clockText = (Text*)(clockGO->GetComponent(TEXT_TYPE));
        if(clockText) clockText->SetText(clock->GetMinutesString() + ":" + clock->GetSecondsString());
    }

    if(isFace) {
        Sprite* faceSprite = (Sprite*)(faceGO->GetComponent(SPRITE_TYPE));
        //TODO set sprites according to player's emotions
    }
}

void MenuHUD::Render() {

}

bool MenuHUD::Is(string type) {
    return type == MENU_HUD_TYPE;
}

void MenuHUD::AddFace() {
    faceGO = new GameObject();
    faceGO->AddComponent(new Sprite(*faceGO, "img/tarma_face.png"));
    faceGO->AddComponent(new CameraFollower(*faceGO, {MARGIN_LEFT, MARGIN_TOP}));
    Game::GetInstance().GetCurrentState().AddObject(faceGO);
}

void MenuHUD::AddLifeIndicator() {
    new LifeManager({faceGO->box.w + MARGIN_LEFT, 0});
    LifeManager::Update();
}

void MenuHUD::AddClock() {
    clockGO = new GameObject();
    clockGO->AddComponent(new Text(*clockGO, "font/Japanese.ttf", 80, Text::BLENDED, "00:00", {255, 255, 255, 255}));
    clockGO->AddComponent(new CameraFollower(*clockGO, Vec2((GAME_WIDTH/2) - clockGO->box.w/2, MARGIN_TOP)));

    clock = new Clock();

    Game::GetInstance().GetCurrentState().AddObject(clockGO);
}
