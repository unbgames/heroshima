//
// Created by edgar on 26/05/18.
//

#include "engine/components/animation/LineTween.h"
#include <utility>

LineTween::LineTween(GameObject &associated, float duration, const Vec2 &from, const Vec2 &to, ActionCallback onAnimationEnd, float startOffset) :
        Animation(associated, duration, move(onAnimationEnd), startOffset), from(from), to(to) {
    associated.box.x = from.x;
    associated.box.y = from.y;
}

void LineTween::onAnimationUpdate(float dt) {
    float linearSpeed = ((from - to).Mag())/duration;
    associated.box += Vec2(linearSpeed*dt, 0).Rotate((to - from).InclX());
}
