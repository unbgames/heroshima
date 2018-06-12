//
// Created by edgar on 28/03/18.
//

#include <engine/Camera.h>
#include <engine/components/Collider.h>
#include "player/Player.h"
#include "engine/components/CollisionTile.h"
#include "engine/components/TileMap.h"
#include "engine/Game.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
    Load(move(file));
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    FILE* fp = fopen((ASSETS_PATH + file).c_str(), "r");
    if(fp == nullptr){
        cout << "Unable to load TileMap: " << file << endl;
        exit(1);
    }

    if(fscanf(fp, "%d,%d,%d", &mapWidth, &mapHeight, &mapDepth) != 3){
        cout << "Error in TileMap dimentions: " << file << endl;
        exit(1);
    }

    int scanned;
    fseek(fp, 1, SEEK_CUR);
    while(!feof(fp)){
        fscanf(fp, " %d,", &scanned);
        tileMatrix.push_back(scanned - 1);
    }

    fclose(fp);
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    return tileMatrix[x + (y * mapWidth) + (z * mapWidth * mapHeight)];
}

void TileMap::Start() {

    // Set Collision Tiles
    for (int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; j++){

            auto index = (unsigned)At(i, j, mapDepth - 1);
            if (index < (unsigned)(tileSet->GetRows() * tileSet->GetColumns()) - 1) {
                auto *collisionGO = new GameObject;
                collisionGO->box = {(int)(i * tileSet->GetTileWidth() - Camera::pos.x - PARALLAX_FACTOR * (mapDepth - 1)),
                                    (int)(j * tileSet->GetTileHeight() - Camera::pos.y - PARALLAX_FACTOR * (mapDepth - 1)),
                                    tileSet->GetTileWidth(),
                                    tileSet->GetTileHeight()};
                collisionGO->AddComponent(new Collider(*collisionGO));
                collisionGO->AddComponent(new CollisionTile(*collisionGO));
                Game::GetInstance().GetCurrentState().AddTileObject(collisionGO);
            }

        }
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; j++){
            auto x = (int)(i * tileSet->GetTileWidth() - cameraX - PARALLAX_FACTOR * layer);
            auto y = (int)(j * tileSet->GetTileHeight() - cameraY - PARALLAX_FACTOR * layer);

            tileSet->RenderTile((unsigned)At(i, j, layer), x, y);
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z, (int)(Camera::pos.x), (int)(Camera::pos.y));
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(string type) {
    return type == TILE_MAP_TYPE;
}

int TileMap::GetWidth() {
    return this->mapWidth;
}

int TileMap::GetHeight() {
    return this->mapHeight;
}

int TileMap::GetDepth() {
    return this->mapDepth;
}

