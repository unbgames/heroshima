//
// Created by edgar on 01/06/18.
//

#ifndef GUNMANAGER_H
#define GUNMANAGER_H

#define GUN_MANAGER_TYPE


#include <Component.h>

class GunManager : public Component {
public:
    GunManager(GameObject &associated, Vec2 offset);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    Vec2 offset;
    StaticSprite pistol;
    GameObject* gunIconGO;
    GameObject* ammoCounterGO;

};


#endif //SRC_GUNMANAGER_H
