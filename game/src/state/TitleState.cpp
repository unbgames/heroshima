//
// Created by edgar on 11/05/18.
//

#include <state/Stage1.h>
#include "engine/components/Text.h"
#include "state/TitleState.h"
#include "engine/InputManager.h"
#include "engine/Game.h"
#include "engine/Camera.h"

TitleState::TitleState() {
    auto titleGO(new GameObject);
    titleGO->AddComponent(new Sprite(*titleGO, "img/Japan_BG_Pixel.jpg"));
    AddObject(titleGO);

    auto redCircleGO(new GameObject);
    redCircleGO->box.x = GAME_WIDTH/2 - redCircleGO->box.w/2;
    Sprite *sprite = new Sprite(*redCircleGO, "img/circle_red.png");
    sprite->SetScale(0.5F, 0.5F);
    redCircleGO->AddComponent(sprite);
    AddObject(redCircleGO);

    auto menuGO(new GameObject);
    menuGO->box += {50, 250};
    menu = new Menu(*menuGO);
    menuGO->AddComponent(menu);
    AddObject(menuGO);

    auto fontGO(new GameObject);
    Text *text = new Text(*fontGO, "font/JAPAN.ttf", 70, Text::TextStyle::BLENDED, "HEROshima", {255, 255, 255, 255});
    fontGO->AddComponent(text);
    Rect &fontBox = fontGO->box;
    fontBox.x = GAME_WIDTH/2 - fontBox.w/2;
    fontBox.y = fontBox.h;
    AddObject(fontGO);

}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {
    backgroundMusic.Open("audio/HEROSHIMAMENU.ogg");
}

void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        Pause();
        Game::GetInstance().Push(new Stage1());
    }

    if(menu->IsSelected()){
        menu->SetSelected(false);
        switch(menu->GetOption()){
            case Menu::NEW_GAME:
                Pause();
                Game::GetInstance().Push(new Stage1());
                break;

            case Menu::CONTROLS:

                break;
                
            case Menu::EXIT_GAME:
                Pause();
                quitRequested = true;
                break;

            default:
                break;
        }
    }
}

void TitleState::Render() {
    RenderArray();
    menu->Render();

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
