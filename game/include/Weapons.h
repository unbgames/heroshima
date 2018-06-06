//
// Created by edgar on 25/05/18.
//

#include <Gun.h>
#include "BodyState.h"

using std::string;

class Weapons{
public:
    static Gun *pistol;
    static Gun *heavy;

    static BodyState *idle;
    static BodyState *walking;

};
