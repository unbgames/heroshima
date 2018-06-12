//
// Created by edgar on 11/05/18.
//

#ifndef TITLESTATE_CLASS
#define TITLESTATE_CLASS


#include "engine/State.h"
#include "engine/Music.h"
#include "Menu.h"

class TitleState : public State {
public:
    TitleState();
    ~TitleState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music backgroundMusic;
    Menu* menu;
};


#endif //SRC_TITLESTATE_H
