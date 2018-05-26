//
// Created by edgar on 25/05/18.
//

#include "Animation.h"

Animation::Animation(GameObject &associated) : Component(associated) {}

Animation::Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration, ActionCallback onAnimationEnd) :
        Component(associated), from(from), to(to), duration(duration), elapsed(0), onAnimationEnd(move(onAnimationEnd)) {
    associated.box.x = from.x - associated.box.w/2;
    associated.box.y = from.y - associated.box.h/2;
}

Animation::Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration) :
        Component(associated), from(from), to(to), duration(duration), elapsed(0) {
    associated.box.x = from.x - associated.box.w/2;
    associated.box.y = from.y - associated.box.h/2;
}

void Animation::Update(float dt) {
    if(elapsed < duration) {
        float linearSpeed = ((from - to).Mag())/duration;
        associated.box += Vec2(linearSpeed*dt, 0).Rotate((to - from).InclX());

    } else{
        associated.RequestDelete();
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
