//
// Created by edgar on 31/05/18.
//

#include <Game.h>
#include <CameraFollower.h>
#include "MenuHUD.h"

MenuHUD::MenuHUD(GameObject &associated, bool isClock) : Component(associated), isClock(isClock) {
    if(isClock){
        AddClock();
    }
}

void MenuHUD::Update(float dt) {
    if(isClock) {
        clock->Update(dt);
        clockText->SetText(clock->GetMinutesString() + ":" + clock->GetSecondsString());
    }
}

void MenuHUD::Render() {

}

bool MenuHUD::Is(string type) {
    return type == MENU_HUD_TYPE;
}

void MenuHUD::AddClock() {
    auto clockGO(new GameObject);
    Text *text = new Text(*clockGO, "font/Japanese.ttf", 60, Text::BLENDED, "00:00", {255, 255, 255, 255});
    clockText = text;
    clockGO->AddComponent(clockText);
    clockGO->AddComponent(new CameraFollower(*clockGO, Vec2((GAME_WIDTH/2) - clockGO->box.w/2, MARGIN_TOP)));

    clock = new Clock();

    Game::GetInstance().GetCurrentState().AddObject(clockGO);
}