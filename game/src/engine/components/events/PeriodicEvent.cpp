//
// Created by edgar on 15/05/18.
//

#include "engine/components/events/PeriodicEvent.h"
#include <utility>

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback callback, ActionCallback restCallback, float restTime, float startOffset) :
        Component(associated), periodTime(periodTime + startOffset), callback(move(callback))  {

    this->restCallback = move(restCallback),
    timer = Timer();
    this->restTime = (restTime == 0 ? periodTime : restTime) + periodTime + startOffset;
    this->startOffset = startOffset;
    call = false;
}

void PeriodicEvent::Update(float dt) {
    timer.Update(dt);

    if(timer.Get() >= startOffset) {
        if (timer.Get() >= periodTime && !call) {
            call = true;
            if (callback) {
                callback();
            }
        }
        if(timer.Get() >= restTime){
            call = false;
            if(restCallback){
                restCallback();
            }
            timer.Set(startOffset);
        }
    }
}

void PeriodicEvent::Render() {}

bool PeriodicEvent::Is(string type) {
    return type == PERIODIC_EVENT_TYPE;
}

