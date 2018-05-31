//
// Created by edgar on 26/05/18.
//

#ifndef SRC_ROTATIONTWEEN_H
#define SRC_ROTATIONTWEEN_H

#include "Animation.h"

/**
 * RotationTween implementation of Animation
 * onAnimationUpdate it interpolates the GameObject associated's rotation in a certain amount of degrees.
 *
 * @param angleDeg the amount of degrees to rotate the GameObject associated
 * @param orientation tells if should rotate clockwise (RIGHT) or counter-clockwise (LEFT)
 *
 * @see Animation.h
 * */

class RotationTween : public Animation{
public:
    explicit RotationTween(GameObject &associated, float duration, float angleDeg, Orientation orientation = Orientation::RIGHT,
            ActionCallback onAnimationEnd = nullptr, float angleOffset = 0);

    void onAnimationUpdate(float dt) override;

private:
    Orientation orientation;
    float angleDeg;

};


#endif //SRC_ROTATIONTWEEN_H
