//
// Created by edgar on 25/05/18.
//

#ifndef SRC_ANIMATION_H
#define SRC_ANIMATION_H

#define ANIMATION_TYPE "Animation"


#include "Component.h"
#include "Timer.h"

class Animation : public Component {
public:
    explicit Animation(GameObject &associated, float duration, ActionCallback onAnimationEnd = nullptr, float startOffset = 0);

    void Render() override;
    bool Is(string type) override;

    virtual void onAnimationUpdate(float dt) = 0;

protected:
    float startOffset;
    float duration;
    Timer timer;

    ActionCallback onAnimationEnd;

private:
    //Update(dt) must be private so that Animation subclasses won't override it
    void Update(float dt) override;

};


#endif //SRC_ANIMATION_H
