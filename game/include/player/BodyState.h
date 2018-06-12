//
// Created by edgar on 06/06/18.
//

#ifndef SRC_BODYSTATE_H
#define SRC_BODYSTATE_H


#include "util/Structs.h"

class BodyState {
public:
    BodyState(StaticSprite current);
    BodyState();

    StaticSprite &GetCurrent();

private:
    StaticSprite current;
};


#endif //SRC_BODYSTATE_H
