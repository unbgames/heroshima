//
// Created by edgar on 31/05/18.
//

#include "TimerEvent.h"

TimerEvent::TimerEvent(GameObject &associated, float timeToEvent, ActionCallback callback) :
        Component(associated), timeToEvent(timeToEvent), callback(move(callback)) {
    timer = Timer();
}

void TimerEvent::Update(float dt) {
    timer.Update(dt);

    if(timer.Get() >= timeToEvent) {
        if(callback){
            callback();
        }
    }
}

void TimerEvent::Render() {}

bool TimerEvent::Is(string type) {
    return type == TIMER_EVENT_TYPE;
}
