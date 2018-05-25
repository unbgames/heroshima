//
// Created by edgar on 25/05/18.
//

#ifndef SRC_ANIMATION_H
#define SRC_ANIMATION_H

#define ANIMATION_TYPE "Animation"


#include "Component.h"

class Animation : public Component {
public:
    Animation(GameObject &associated);

    Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration,
              ActionCallback onAnimationEnd);

    Animation(GameObject &associated, const Vec2 &from, const Vec2 &to, float duration);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

private:
    Vec2 from;
    Vec2 to;
    float duration;
    float elapsed;

    ActionCallback onAnimationEnd;

};


#endif //SRC_ANIMATION_H
