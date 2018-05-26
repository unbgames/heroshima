//
// Created by edgar on 15/05/18.
//

#ifndef PERIODEVENT_CLASS
#define PERIODEVENT_CLASS

#include <Timer.h>
#include <functional>
#include "Component.h"

#define PERIODIC_EVENT_TYPE "PeriodicEvent"

/**
 * Periodic Event Component
 * You can define an action (callback) to be executed as soon as a defined time (periodTime) has passed,
 * If you prefer, you can set the specific rest time (restTime), and the action that will occur after him (restCallback)
 */

class PeriodicEvent : public Component {
public:
    PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb);
    PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset);
    PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset, float restTime);
    PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, float startOffset, float restTime, ActionCallback restCallback);
    PeriodicEvent(GameObject &associated, float periodTime, ActionCallback cb, ActionCallback restCallback);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    float startOffset;
    float periodTime;
    float restTime;
    Timer timer;
    bool call;

    ActionCallback callback;
    ActionCallback restCallback;
};


#endif //SRC_PERIODEVENT_H
