//
// Created by edgar on 09/04/18.
//

#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include "GameObject.h"
#include "Timer.h"

#define CAMERA_SPEED    300
#define VERTICAL_OFFSET 150
#define COLLISION_OFFSET 50
#define BODY_OFFSET 571

class Camera {
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;
    static bool followX, followY;

    static void Wiggle(float duration);
    static bool wiggle;

private:
    static GameObject *focus;
    static Timer timer;
    static float wiggleDuration;

};


#endif //SRC_CAMERA_H
