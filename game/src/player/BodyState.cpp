//
// Created by edgar on 06/06/18.
//

#include "player/BodyState.h"

BodyState::BodyState(StaticSprite current) : current(current) {}

BodyState::BodyState() {}

StaticSprite &BodyState::GetCurrent() {
    return current;
}

