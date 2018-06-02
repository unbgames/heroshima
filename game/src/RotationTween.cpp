//
// Created by edgar on 26/05/18.
//

#include "RotationTween.h"
#include <utility>

RotationTween::RotationTween(GameObject &associated, float duration, float angleDeg, Orientation orientation,
                             ActionCallback onAnimationEnd, float angleOffset) :
        Animation(associated, duration, move(onAnimationEnd)), orientation(orientation), angleDeg(angleDeg) {
    associated.angleDeg += angleOffset;
}

void RotationTween::onAnimationUpdate(float dt) {
    float angularSpeed = angleDeg/duration;
    associated.angleDeg += (orientation == Orientation::RIGHT ? angularSpeed : - angularSpeed) * dt;
}
