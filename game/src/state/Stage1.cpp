//
// Created by edgar on 17/05/18.
//

#include <Camera.h>
#include <CameraFollower.h>
#include <Game.h>
#include "TileMap.h"
#include <InputManager.h>
#include <SpriteSheet.h>
#include <MenuHUD.h>
#include <Player.h>
#include "Stage1.h"

Stage1::Stage1() {
    started = false;

    auto bgGO(new GameObject);
    bgGO->AddComponent(new CameraFollower(*bgGO));
    Sprite *bgSprite = new Sprite(*bgGO, "img/bg2.png");
    bgGO->AddComponent(bgSprite);
    AddObject(bgGO);

    auto mapGO(new GameObject);
    mapGO->box.w = GAME_WIDTH;
    mapGO->box.h = GAME_HEIGHT;
    TileSet *tileSet = new TileSet(128, 128, "img/HIROSHIMA-LV1-128x128.png");
    TileMap *tileMap = new TileMap(*mapGO, "map/HIROSHIMA-LV1-128x128.txt", tileSet);
    mapGO->AddComponent(tileMap);
    AddObject(mapGO);

    auto playerGO(new GameObject);
    playerGO->AddComponent(new Player(*playerGO));
    playerGO->box += {50, GAME_HEIGHT - playerGO->box.h - 512};
    AddCollisionObject(playerGO, {0.4, 0.9}, {-8, -COLLISION_OFFSET});

    quitRequested = false;
}

void Stage1::LoadAssets() {
    backgroundMusic.Open("audio/FASE1HEROJAZZBl.ogg");
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

    //cout<<"objetos: " << objectArray.size() << " tiles: " << tileObjectArray.size() << " colliders: " << collisionObjectArray.size() <<endl;
}

void Stage1::Render() {
    RenderArray();
}

void Stage1::Start() {
    StartArray();
    LoadAssets();
    backgroundMusic.Play();

    auto menuHUDGO(new GameObject);
    menuHUDGO->AddComponent(new MenuHUD(*menuHUDGO));
    AddObject(menuHUDGO);

    AddEntitiesFromXML("map/Stage1.xml");
}

void Stage1::Pause() {

}

void Stage1::Resume() {

}
