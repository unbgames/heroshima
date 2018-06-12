//
// Created by edgar on 25/05/18.
//

#include <player/Gun.h>
#include "BodyState.h"

using std::string;

class SpriteSheet{
public:
    static Gun *pistol;
    static Gun *heavy;

    static BodyState *idle;
    static BodyState *walking;

};
