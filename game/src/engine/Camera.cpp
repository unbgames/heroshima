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
    } else {
        InputManager inputManager = InputManager::GetInstance();

        speed = {0, 0};
        Vec2 direcional = {CAMERA_SPEED * dt, 0};

        bool right = inputManager.IsKeyDown(RIGHT_ARROW_KEY);
        bool down = inputManager.IsKeyDown(DOWN_ARROW_KEY);
        bool left = inputManager.IsKeyDown(LEFT_ARROW_KEY);
        bool up = inputManager.IsKeyDown(UP_ARROW_KEY);

        if (right) {
            speed = direcional;
        } else if (down) {
            speed = direcional.Rotate((float) M_PI / 2);
        } else if (left) {
            speed = direcional.Rotate((float) M_PI);
        } else if (up) {
            speed = direcional.Rotate((float) -M_PI / 2);
        }

        if (right && down) {
            speed = direcional.Rotate((float) M_PI / 4);
        } else if (left && down) {
            speed = direcional.Rotate((float) 3 * M_PI / 4);
        } else if (left && up) {
            speed = direcional.Rotate((float) -3 * M_PI / 4);
        } else if (right && up) {
            speed = direcional.Rotate((float) -M_PI / 4);
        }

        pos += speed;
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
