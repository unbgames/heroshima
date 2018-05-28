//
// Created by edgar on 17/05/18.
//

#include <Camera.h>
#include <Player.h>
#include <Sprite.h>
#include <CameraFollower.h>
#include <Game.h>
#include "TileMap.h"
#include "Collider.h"
#include "TileSet.h"
#include <InputManager.h>
#include "Stage1.h"

Stage1::Stage1() {
    started = false;

    auto bgGO(new GameObject);
    bgGO->AddComponent(new CameraFollower(*bgGO));
    Sprite *bgSprite = new Sprite(*bgGO, "img/bg_temp.gif");
    bgSprite->SetScale(2.68F, 2.68F);
    bgGO->AddComponent(bgSprite);
    AddObject(bgGO);

    auto mapGO(new GameObject);
    mapGO->box.w = GAME_WIDTH;
    mapGO->box.h = GAME_HEIGHT;
    TileSet *tileSet = new TileSet(32, 32, "img/tileset-test.png");
    TileMap *tileMap = new TileMap(*mapGO, "map/map-test.txt", tileSet);
    mapGO->AddComponent(tileMap);
    AddObject(mapGO);

    auto playerGO(new GameObject);
    playerGO->AddComponent(new Player(*playerGO));
    playerGO->box += {0, GAME_HEIGHT - playerGO->box.h - 32 * 2};
    Camera::Follow(playerGO);
    AddObject(playerGO);

    quitRequested = false;
}

void Stage1::LoadAssets() {
    backgroundMusic.Open("audio/stageState.ogg");
}

void Stage1::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();

    Camera::Update(dt);

    quitRequested = inputManager.QuitRequested();

    popRequested = inputManager.KeyPress(ESCAPE_KEY);

    if(inputManager.KeyPress(SDLK_F6)) {
        setDebug(!isDebug());
    }

    UpdateArray(dt);

    IsDeadArray();

    TestCollision();
}

void Stage1::Render() {
    RenderArray();
}

void Stage1::Start() {
    StartArray();
    LoadAssets();
    backgroundMusic.Play();
//    Camera::pos = Vec2(0, 0);
}

void Stage1::Pause() {

}

void Stage1::Resume() {

}
