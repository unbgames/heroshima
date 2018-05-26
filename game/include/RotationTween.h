//
// Created by edgar on 26/05/18.
//

#ifndef SRC_ROTATIONTWEEN_H
#define SRC_ROTATIONTWEEN_H


#include "Animation.h"

class RotationTween : public Animation{
public:
    explicit RotationTween(GameObject &associated, float duration, Orientation orientation = Orientation::RIGHT,
            float angleDeg = 0, ActionCallback onAnimationEnd = nullptr, float angleOffset = 0);

    void onAnimationUpdate(float dt) override;

private:
    Orientation orientation;
    float angleDeg;

};


#endif //SRC_ROTATIONTWEEN_H
