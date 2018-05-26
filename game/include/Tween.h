//
// Created by edgar on 26/05/18.
//

#ifndef SRC_TWEEN_H
#define SRC_TWEEN_H


#include "Animation.h"

class Tween : public Animation {
public:
    Tween(GameObject &associated);
    Tween(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration, ActionCallback onAnimationEnd);

    void onAnimate(float dt) override;

private:
    Vec2 from;
    Vec2 to;

};


#endif //SRC_TWEEN_H
