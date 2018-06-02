//
// Created by edgar on 25/05/18.
//

#ifndef SRC_ANIMATION_H
#define SRC_ANIMATION_H

#define ANIMATION_TYPE "Animation"


#include "Component.h"
#include "Timer.h"

/**
 * Abstract class Animation
 * It is a abstract class for all Animations, must be instantiated only by it subclasses.
 * Every subclass must override the onAnimationUpdate(float dt) method and implement its own behaviour.
 * It defines a startOffset to begin the animation and a duration of the animation itself.
 * When the animation ends, it calls the onAnimationEnd callback, if exists.
 *
 * */

class Animation : public Component {
public:
    void Render() override;
    bool Is(string type) override;

    virtual void onAnimationUpdate(float dt) = 0;

protected:
    //Only Animation subclasses must instantiate it
    explicit Animation(GameObject &associated, float duration, ActionCallback onAnimationEnd = nullptr, float startOffset = 0);

    float startOffset;
    float duration;

    ActionCallback onAnimationEnd;

private:
    //Update(dt) must be private so that Animation's subclasses won't be able to override it
    void Update(float dt) override;
    Timer timer;

};


#endif //SRC_ANIMATION_H
