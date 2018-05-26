//
// Created by edgar on 25/05/18.
//

#include "Animation.h"

Animation::Animation(GameObject &associated) : Component(associated) {}

Animation::Animation(GameObject &associated, float duration) : Component(associated), duration(duration) {}

Animation::Animation(GameObject &associated, float duration, ActionCallback &onAnimationEnd)
        : Component(associated), duration(duration), onAnimationEnd(onAnimationEnd) {}

void Animation::Update(float dt) {
    if(elapsed < duration) {
        onAnimate(dt);
    } else{
        if(onAnimationEnd){
            onAnimationEnd();
        }
    }
    elapsed += dt;
}

void Animation::Render() {}

bool Animation::Is(string type) {
    return type == ANIMATION_TYPE;
}
