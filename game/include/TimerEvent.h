//
// Created by edgar on 31/05/18.
//

#ifndef TIMEREVENT_H
#define TIMEREVENT_H

#define TIMER_EVENT_TYPE "TimerEvent"


#include "Component.h"
#include "Timer.h"

/**
 * TimerEvent Component
 * Lets you call a callback after a certain amount of time.
 *
 * @param associated the GameObject associated to this component
 * @param timeToEvent amount of time in seconds to call the callback
 * @param the callback to be called
 *
 * @note When the callback ends, the associated GameObject is auto destroyed
 * */

class TimerEvent : public Component {
public:
    TimerEvent(GameObject &associated, float timeToEvent, ActionCallback callback);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    float timeToEvent;
    Timer timer;

    ActionCallback callback;

};


#endif //SRC_TIMEREVENT_H
