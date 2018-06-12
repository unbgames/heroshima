//
// Created by edgar on 09/05/18.
//

#include "util/Timer.h"

Timer::Timer(): time(0){}

void Timer::Update(float dt) {
    time += dt;
}

void Timer::Restart() {
    time = 0;
}

void Timer::Set(float t) {
    time = t;
}

float Timer::Get() {
    return time;
}
