//
// Created by edgar on 31/05/18.
//

#include "Clock.h"

Clock::Clock() : seconds(0), minutes(0) {}

Clock::Clock(int minutes, float seconds) {
    Set(minutes, seconds);
}

void Clock::Update(float dt) {
    if(seconds < 60){
        seconds += dt;
    } else{
        seconds = 0;
        minutes++;
    }
}

void Clock::Restart() {
    Set(0, 0);
}

void Clock::Set(int minutes, float seconds) {
    this->minutes = minutes;
    if(seconds < 60){
        this->seconds = seconds;
    } else{
        this->seconds = (int)seconds % 60;
        this->minutes += seconds / 60;
    }
}

int Clock::GetMinutes() {
    return minutes;
}

int Clock::GetSeconds() {
    return (int)seconds;
}

string Clock::GetMinutesString() {
    return (minutes < 10 ? "0" : "") + to_string(minutes);
}

string Clock::GetSecondsString() {
    return ((int)seconds < 10 ? "0" : "") + to_string((int)seconds);
}
