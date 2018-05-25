//
// Created by edgar on 25/05/18.
//

#include "Animation.h"

Animation::Animation(GameObject &associated) : Component(associated) {}

Animation::Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration, ActionCallback onAnimationEnd) :
        Component(associated), from(from), to(to), duration(duration), elapsed(0) {

    onAnimationEnd = move(onAnimationEnd);
}

Animation::Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration) :
        Component(associated), from(from), to(to), duration(duration), elapsed(0) {

}

void Animation::Update(float dt) {
    if(elapsed < duration) {
        float distance = (from - to).Mag();
        float speed = distance/duration;
        Vec2 deltaX = {speed * dt, 0};
        Vec2 calculado = to - Vec2(associated.box.x + (associated.box.w / 2), associated.box.y + (associated.box.h / 2));
        Vec2 real = deltaX.Rotate(calculado.InclX());

        if (calculado.Mag() < real.Mag()) {
            associated.box += calculado;
        }
    } else{
        associated.RequestDelete();
        onAnimationEnd();
    }
    elapsed += dt;
}

void Animation::Render() {}

bool Animation::Is(string type) {
    return type == ANIMATION_TYPE;
}
