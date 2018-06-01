//
// Created by edgar on 01/06/18.
//

#ifndef SRC_LIFEMANAGER_H
#define SRC_LIFEMANAGER_H

#define LIFE_MANAGER_TYPE "LifeManager"
#define GAP 15
#define MARGIN_TOP 80


#include "Component.h"

class LifeManager : public Component {
public:
    LifeManager(GameObject &associated, Vec2 offset);

    virtual ~LifeManager();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    Vec2 offset;
    vector<weak_ptr<GameObject>> hearts;

};


#endif //SRC_LIFEMANAGER_H
