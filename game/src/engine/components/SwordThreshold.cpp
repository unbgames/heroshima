//
// Created by edgar on 08/07/18.
//

#include <Collider.h>
#include "SwordThreshold.h"

SwordThreshold::SwordThreshold(GameObject &associated) : Component(associated) {
    associated.AddComponent(new Collider(associated));
}

bool SwordThreshold::Is(string type) {
    return type == SWORD_THRESHOLD_TYPE;
}

void SwordThreshold::Start() {}

void SwordThreshold::Update(float dt) {}

void SwordThreshold::Render() {}
