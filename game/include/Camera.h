//
// Created by edgar on 09/04/18.
//

#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include "GameObject.h"

#define CAMERA_SPEED    300
#define VERTICAL_OFFSET 150
#define BODY_OFFSET 571

class Camera {
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;
    static bool followX, followY;

private:
    static GameObject *focus;

};


#endif //SRC_CAMERA_H
