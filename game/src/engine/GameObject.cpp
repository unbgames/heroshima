//
// Created by edgar on 23/03/18.
//

#include "engine/GameObject.h"

GameObject::GameObject() {

    this->isDead = false;
    this->orientation = RIGHT;
    this->started = false;
    this->angleDeg = 0;
}

GameObject::~GameObject() {
    for(auto it = components.rbegin(); it != components.rend(); ++it) {
        (*it).reset();
    }
    components.clear();
}

void GameObject::Start() {
    for (auto &component : components) {
        component->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for (auto &component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto &component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.emplace_back(cpt);
    if(started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component *cpt) {
    for(unsigned i = 0; i < components.size(); ++i){
        if(components[i].get() == cpt){
            components.erase(components.begin() + i);
            break;
        }
    }
}

Component *GameObject::GetComponent(string type) {
    for(unsigned i = 0; i < components.size(); i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject &other) {
    for(unsigned i = 0; i < components.size(); i++){
        components[i]->NotifyCollision(other);
    }
}
