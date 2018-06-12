//
// Created by edgar on 26/05/18.
//

#ifndef SRC_LINETWEEN_H
#define SRC_LINETWEEN_H

#include "Animation.h"

/**
 * LineTween implementation of Animation
 * onAnimationUpdate it interpolates the GameObject associated's box position from a position to other.
 *
 * @param from the start position
 * @param to the end position
 *
 * @see Animation.h
 * */

class LineTween : public Animation {
public:
    explicit LineTween(GameObject &associated, float duration, const Vec2 &from, const Vec2 &to,
                       ActionCallback onAnimationEnd = nullptr, float startOffset = 0);

    void onAnimationUpdate(float dt) override;

private:
    Vec2 from;
    Vec2 to;

};


#endif //SRC_TWEEN_H
