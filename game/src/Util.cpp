//
// Created by edgar on 04/06/18.
//

#include <cstdlib>
#include "Util.h"

float Util::floatRand(float min, float max) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}
