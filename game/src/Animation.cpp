//
// Created by edgar on 25/05/18.
//

#include "Animation.h"

Animation::Animation(GameObject &associated) : Component(associated), startOffset(0) {
    timer = Timer();
}

Animation::Animation(GameObject &associated, float duration) : Component(associated), duration(duration), startOffset(0) {
    timer = Timer();
}

Animation::Animation(GameObject &associated, float duration, float startOffset) : 
        Component(associated), duration(duration + startOffset), startOffset(startOffset) {
    timer = Timer();
}

Animation::Animation(GameObject &associated, float duration, ActionCallback &onAnimationEnd)
        : Component(associated), duration(duration), onAnimationEnd(onAnimationEnd), startOffset(0) {
    timer = Timer();
}
        
Animation::Animation(GameObject &associated, float duration, float startOffset, ActionCallback &onAnimationEnd)
        : Component(associated), duration(duration + startOffset), onAnimationEnd(onAnimationEnd), startOffset(startOffset) {
    timer = Timer();
}

void Animation::Update(float dt) {
    if(timer.Get() >= startOffset) {
        if (timer.Get() < duration) {
            onAnimate(dt);
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
