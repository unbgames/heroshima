//
// Created by edgar on 09/04/18.
//

#include <Game.h>
#include "InputManager.h"
#include "Camera.h"

Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed = *new Vec2();
GameObject *Camera::focus = nullptr;
Timer Camera::timer = Timer();
bool Camera::followX = false;
bool Camera::followY = false;
bool Camera::wiggle = false;
float Camera::wiggleDuration = 0;

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    followX = followY = false;
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus != nullptr){
        if(focus->box.y < GAME_HEIGHT){
            pos = {- GAME_WIDTH/2, - GAME_HEIGHT + VERTICAL_OFFSET + BODY_OFFSET};

            if(followX){
                pos += {focus->box.x, 0};
            }
            if(followY){
                pos += {0, focus->box.y - BODY_OFFSET};
            }
        }
    }

    if(wiggle){
        timer.Update(dt);
        float delta = timer.Get();
        pos += Vec2(sin(delta * 100), cos(delta * 100)) * 10;
        if(delta > wiggleDuration){
            timer.Restart();
            wiggle = false;
        }
    }
}

void Camera::Wiggle(float duration) {
    wiggleDuration  = duration;
    wiggle = true;
}
