//
// Created by edgar on 11/05/18.
//

#include "Text.h"
#include <PeriodicEvent.h>
#include "TitleState.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

TitleState::TitleState() {
    auto titleGO(new GameObject);
    titleGO->AddComponent(new Sprite(*titleGO, "img/Japan_BG_Pixel.jpg"));
    AddObject(titleGO);

    auto fontGO(new GameObject);
    Text *text = new Text(*fontGO, "font/JAPAN.ttf", 60, Text::TextStyle::SOLID, "HEROshima", {255, 255, 255, 255});
    fontGO->AddComponent(text);
    Rect &fontBox = fontGO->box;
    fontBox.x = GAME_WIDTH/2 - fontBox.w/2;
    fontBox.y = fontBox.h;

    AddObject(fontGO);

}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {
    backgroundMusic.Open("audio/Japans-Victory-Theme.ogg");
}

void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    LoadAssets();
    StartArray();
    backgroundMusic.Play();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
    Camera::pos = Vec2(0, 0);
    backgroundMusic.Play();
}
