//
// Created by edgar on 25/05/18.
//

#include "engine/components/animation/Animation.h"
#include <utility>

Animation::Animation(GameObject &associated, float duration, ActionCallback onAnimationEnd, float startOffset)
        : Component(associated), duration(duration + startOffset) {

    this->onAnimationEnd = move(onAnimationEnd);
    this->startOffset = startOffset;
    this->timer = Timer();
}

void Animation::Update(float dt) {
    if(timer.Get() >= startOffset) {
        if (timer.Get() < duration) {
            onAnimationUpdate(dt);
        } else {
            if (onAnimationEnd) {
                onAnimationEnd();
            }
        }
    }
    timer.Update(dt);
}

void Animation::Render() {}

bool Animation::Is(string type) {
    return type == ANIMATION_TYPE;
}
