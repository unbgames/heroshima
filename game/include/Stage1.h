//
// Created by edgar on 17/05/18.
//

#ifndef STAGE1_CLASS
#define STAGE1_CLASS

#include "Music.h"
#include "State.h"

class Stage1 : public State {
public:
    Stage1();

    void LoadAssets() override;

    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music backgroundMusic;
};


#endif //SRC_STAGE1_H
