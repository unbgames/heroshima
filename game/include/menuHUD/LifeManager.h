//
// Created by edgar on 01/06/18.
//

#ifndef SRC_LIFEMANAGER_H
#define SRC_LIFEMANAGER_H

#define GAP 15
#define TOP_MARGIN 80

#include "engine/Component.h"

class LifeManager {
public:
    explicit LifeManager(Vec2 offset);

    virtual ~LifeManager();

    static void Update();


private:
    static Vec2 startOffset;
    static Vec2 offset;
    static vector<weak_ptr<GameObject>> hearts;
    static int lastHp;

};


#endif //SRC_LIFEMANAGER_H
