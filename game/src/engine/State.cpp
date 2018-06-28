//
// Created by edgar on 10/05/18.
//

#include "State.h"
#include <Collider.h>
#include <Collision.h>
#include <Game.h>
#include <WalkingShootingEnemy.h>
#include <FallingChasingEnemy.h>
#include <LifeCrate.h>
#include <Sprite.h>
#include <WeaponCrate.h>
#include <SpriteSheet.h>
#include "../xml/pugixml.hpp"

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
    for(auto it = objectArray.rbegin(); it != objectArray.rend(); ++it) {
        (*it).reset();
    }
    objectArray.clear();
    for(auto it = collisionObjectArray.rbegin(); it != collisionObjectArray.rend(); ++it) {
        (*it).reset();
    }
    collisionObjectArray.clear();
    for(auto it = tileObjectArray.rbegin(); it != tileObjectArray.rend(); ++it) {
        (*it).reset();
    }
    tileObjectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject *go) {
    shared_ptr<GameObject> gameObject(go);
    objectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for (auto &i : objectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}

weak_ptr<GameObject> State::AddTileObject(GameObject *go) {
    shared_ptr<GameObject> gameObject(go);
    tileObjectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);
}

weak_ptr<GameObject> State::GetTileObjectPtr(GameObject *go) {
    for (auto &i : tileObjectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}

weak_ptr<GameObject> State::AddCollisionObject(GameObject *go) {
    shared_ptr<GameObject> gameObject(go);
    collisionObjectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);
}

weak_ptr<GameObject> State::GetCollisionObjectPtr(GameObject *go) {
    for (auto &i : collisionObjectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for (unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Start();
    }
    for (unsigned i = 0; i < collisionObjectArray.size(); i++){
        collisionObjectArray[i].get()->Start();
    }
    for (unsigned i = 0; i < tileObjectArray.size(); i++){
        tileObjectArray[i].get()->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for (unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }

    for (unsigned i = 0; i < collisionObjectArray.size(); i++){
        collisionObjectArray[i].get()->Update(dt);
    }

    for (unsigned i = 0; i < tileObjectArray.size(); i++) {
        for (unsigned j = 0; j < collisionObjectArray.size(); j++) {
            auto collider = (Collider*) tileObjectArray[i]->GetComponent(COLLIDER_TYPE);
            if (tileObjectArray[i]->box.DistRecs(collisionObjectArray[j]->box) < MINIMUM_COLLIDER_DIST) {
                if (collider == nullptr) {
                    collider = new Collider(*tileObjectArray[i]);
                    tileObjectArray[i]->AddComponent(collider);
                }
                break;
            } else {
                if (collider != nullptr) {
                    tileObjectArray[i]->RemoveComponent(collider);
                }
            }
        }
        tileObjectArray[i].get()->Update(dt);
    }
}

void State::RenderArray() {
    for (unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Render();
    }
    for (unsigned i = 0; i < collisionObjectArray.size(); i++){
        collisionObjectArray[i].get()->Render();
    }
    for (unsigned i = 0; i < tileObjectArray.size(); i++){
        tileObjectArray[i].get()->Render();
    }
}

void State::IsDeadArray() {
    for(unsigned i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
    for(unsigned i = 0; i < collisionObjectArray.size(); i++) {
        if (collisionObjectArray[i]->IsDead()) {
            collisionObjectArray.erase(collisionObjectArray.begin() + i);
        }
    }
}

bool State::isDebug() const {
    return debug;
}

void State::setDebug(bool debug) {
    this->debug = debug;
}

void State::TestCollision() {
    for (unsigned i = 0; i < collisionObjectArray.size(); i++) {
        //Tests collision with others objects in objectArray
        for(unsigned j = i+1; j < collisionObjectArray.size(); j++){
            auto &objA = collisionObjectArray[i];
            auto &objB = collisionObjectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent(COLLIDER_TYPE);
            Collider *colliderB = (Collider*) objB->GetComponent(COLLIDER_TYPE);
            if(colliderA && colliderB){
                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(colliderA, colliderB, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
        //Tests collision with tiles in tileObjectArray
        for(unsigned j = 0; j < tileObjectArray.size(); j++){
            auto &objA = collisionObjectArray[i];
            auto &objB = tileObjectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent(COLLIDER_TYPE);
            Collider *colliderB = (Collider*) objB->GetComponent(COLLIDER_TYPE);
            if(colliderA && colliderB){
                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(colliderA, colliderB, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
    }
}

void State::AddEntitiesFromXML(string xml) {
    pugi::xml_document doc;
    doc.load_file((ASSETS_PATH + xml).c_str());

    pugi::xml_node stage = doc.child("stage");

    for (pugi::xml_node enemy = stage.child("enemies").child("enemy"); enemy; enemy = enemy.next_sibling("enemy")) {
        const pugi::char_t *name = enemy.child("name").text().get();
        int hp = enemy.child("hp").text().as_int();
        float x = enemy.child("x").text().as_float();
        float y = enemy.child("y").text().as_float();

        AddEnemy(name, hp, Vec2(x, y));
    }

    for (pugi::xml_node enemy = stage.child("crates").child("crate"); enemy; enemy = enemy.next_sibling("crate")) {
        const pugi::char_t *type = enemy.child("type").text().get();
        float x = enemy.child("x").text().as_float();
        float y = enemy.child("y").text().as_float();
        int health = enemy.child("health").text().as_int();
        bool startFalling = enemy.child("startFalling").text().as_bool();

        AddCrate(type, health, Vec2(x, y), startFalling);
    }
}

void State::AddEnemy(string name, int hp, Vec2 pos) {
    auto enemyGO(new GameObject);
    Enemy *enemy;

    if(name == "WalkingShootingEnemy"){
        enemy = new WalkingShootingEnemy(*enemyGO, hp, pos);
    } else if(name == "FallingChasingEnemy"){
        enemy = new FallingChasingEnemy(*enemyGO, hp, pos);
    }

    enemyGO->AddComponent(enemy);
    AddCollisionObject(enemyGO);
}

void State::AddCrate(string type, int health, Vec2 pos, bool startFalling) {
    auto crateGO(new GameObject);

    if(type == "life"){
        crateGO->AddComponent(new LifeCrate(*crateGO, pos, health, startFalling));
    } else if(type == "heavy"){
        crateGO->AddComponent(new Sprite(*crateGO, "img/heavy_crate.png"));
        crateGO->AddComponent(new WeaponCrate(*crateGO, pos, SpriteSheet::heavy, startFalling));
    }

    AddCollisionObject(crateGO);
}
