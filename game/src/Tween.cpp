//
// Created by edgar on 26/05/18.
//

#include "Tween.h"

Tween::Tween(GameObject &associated) : Animation(associated) {}

Tween::Tween(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration, ActionCallback onAnimationEnd) :
        Animation(associated, duration, onAnimationEnd), from(from), to(to) {
    associated.box.x = from.x - associated.box.w/2;
    associated.box.y = from.y - associated.box.h/2;
}

void Tween::onAnimate(float dt) {
    float linearSpeed = ((from - to).Mag())/duration;
    associated.box += Vec2(linearSpeed*dt, 0).Rotate((to - from).InclX());
}
