//
// Created by edgar on 25/05/18.
//

#include "Animation.h"
#include <utility>

Animation::Animation(GameObject &associated, float duration, ActionCallback onAnimationEnd, float startOffset)
        : Component(associated), duration(duration + startOffset), onAnimationEnd(move(onAnimationEnd)), startOffset(startOffset) {
    timer = Timer();
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