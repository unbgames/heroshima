//
// Created by edgar on 15/05/18.
//

#ifndef PERIODEVENT_CLASS
#define PERIODEVENT_CLASS

#include <Timer.h>
#include <functional>
#include "Component.h"

#define PERIODIC_EVENT_TYPE "PeriodicEvent"

class PeriodicEvent : public Component {
public:
    PeriodicEvent(GameObject &associated, float period, ActionCallback cb);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    float period;
    Timer timer;

    ActionCallback callback;
};


#endif //SRC_PERIODEVENT_H
