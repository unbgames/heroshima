//
// Created by edgar on 08/07/18.
//

#ifndef SRC_SWORDTHRESHOLD_H
#define SRC_SWORDTHRESHOLD_H

#define SWORD_THRESHOLD_TYPE "SwordThreshold"


#include <Component.h>

class SwordThreshold : public Component {
public:
    explicit SwordThreshold(GameObject &associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    bool Is(string type) override;

};


#endif //SRC_SWORDTHRESHOLD_H
