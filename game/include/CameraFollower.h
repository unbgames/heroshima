//
// Created by edgar on 10/04/18.
//

#ifndef CAMERAFOLLOWER_CLASS
#define CAMERAFOLLOWER_CLASS


#include <Component.h>

#define CAMERA_FOLLOWER_TYPE "CameraFollower"

class CameraFollower : public Component {
public:
    explicit CameraFollower(GameObject &associated, Vec2 offset = {0, 0});

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    Vec2 offset;

};

#endif //SRC_CAMERAFOLLOWER_H
