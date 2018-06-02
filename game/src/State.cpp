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

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for(unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for(unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }
}

void State::RenderArray() {
    for(unsigned i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Render();
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
    }
}
