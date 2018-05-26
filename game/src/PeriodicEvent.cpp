//
// Created by edgar on 15/05/18.
//

#include "PeriodicEvent.h"
#include <utility>

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb) :
        Component(associated), periodTime(periodTime),
        callback(move(cb)), timer(Timer()),
        startOffset(0), restTime(this->periodTime), restCallback(nullptr) {
    call = false;
}

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset) :
        Component(associated), periodTime(periodTime + startOffset),
        callback(move(cb)), timer(Timer()),
        startOffset(startOffset), restTime(this->periodTime), restCallback(nullptr){
    call = false;
}

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset, float restTime) :
        Component(associated), periodTime(periodTime + startOffset),
        callback(move(cb)), timer(Timer()),
        startOffset(startOffset), restTime(this->periodTime + restTime), restCallback(nullptr){
    call = false;
}

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset, float restTime, ActionCallback restCallback) :
        Component(associated), periodTime(periodTime + startOffset),
        callback(move(cb)), timer(Timer()),
        startOffset(startOffset), restTime(this->periodTime + restTime), restCallback(move(restCallback)){
    call = false;
}

PeriodicEvent::PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, ActionCallback restCallback) :
        Component(associated), periodTime(periodTime),
        callback(move(cb)), timer(Timer()),
        startOffset(0), restTime(periodTime * 2), restCallback(move(restCallback)){
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

