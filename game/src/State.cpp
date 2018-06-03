//
// Created by edgar on 10/05/18.
//

#include "State.h"
#include <Collider.h>
#include <Collision.h>

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
    for(auto it = objectArray.rbegin(); it != objectArray.rend(); ++it) {
        (*it).reset();
    }
    objectArray.clear();

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
    for (unsigned i = 0; i < tileObjectArray.size(); i++){
        tileObjectArray[i].get()->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for (unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }
    for (unsigned i = 0; i < tileObjectArray.size(); i++) {
        for (unsigned j = 0; j < objectArray.size(); j++) {
            auto collider = (Collider*) tileObjectArray[i]->GetComponent(COLLIDER_TYPE);
            if (tileObjectArray[i]->box.DistRecs(objectArray[j]->box) < MINIMUM_COLLIDER_DIST) {
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
}

bool State::isDebug() const {
    return debug;
}

void State::setDebug(bool debug) {
    this->debug = debug;
}

void State::TestCollision() {
    for (unsigned i = 0; i < objectArray.size(); i++) {
        for(unsigned j = i+1; j < objectArray.size(); j++){
            auto &objA = objectArray[i];
            auto &objB = objectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent(COLLIDER_TYPE);
            Collider *colliderB = (Collider*) objB->GetComponent(COLLIDER_TYPE);
            if(colliderA && colliderB){
                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(colliderA, colliderB, angleOfA, angleOfB)) {
                    Collision::IsColliding(colliderB, colliderA, angleOfB, angleOfA);//TODO optimize
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
        for(unsigned j = 0; j < tileObjectArray.size(); j++){
            auto &objA = objectArray[i];
            auto &objB = tileObjectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent(COLLIDER_TYPE);
            Collider *colliderB = (Collider*) objB->GetComponent(COLLIDER_TYPE);
            if(colliderA && colliderB){
                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsColliding(colliderA, colliderB, angleOfA, angleOfB)) {
                    Collision::IsColliding(colliderB, colliderA, angleOfB, angleOfA);//TODO optimize
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
    }
}
