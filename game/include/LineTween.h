//
// Created by edgar on 26/05/18.
//

#ifndef SRC_LINETWEEN_H
#define SRC_LINETWEEN_H

#include "Animation.h"

class LineTween : public Animation {
public:
    LineTween(GameObject &associated);
    LineTween(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration, ActionCallback onAnimationEnd);

    void onAnimate(float dt) override;

private:
    Vec2 from;
    Vec2 to;

};


#endif //SRC_TWEEN_H
