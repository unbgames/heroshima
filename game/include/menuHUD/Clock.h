//
// Created by edgar on 31/05/18.
//

#ifndef SRC_CLOCK_H
#define SRC_CLOCK_H

#include <string>

using std::string;
using std::to_string;

class Clock {
public:
    Clock();
    Clock(int minutes, float seconds);

    void Update(float dt);
    void Restart();
    void Set(int minutes, float seconds);
    int GetMinutes();
    int GetSeconds();
    string GetMinutesString();
    string GetSecondsString();

private:
    float seconds;
    int minutes;

};


#endif //SRC_CLOCK_H
