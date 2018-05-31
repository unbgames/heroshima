//
// Created by edgar on 10/04/18.
//

#include "../include/Camera.h"
#include "../include/CameraFollower.h"

CameraFollower::CameraFollower(GameObject &associated, Vec2 offset) : Component(associated), offset(offset) {

}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x + offset.x;
    associated.box.y = Camera::pos.y + offset.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(string type) {
    return type == CAMERA_FOLLOWER_TYPE;
}
