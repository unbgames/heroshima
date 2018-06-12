//
// Created by edgar on 16/03/18.
//

#ifndef SPRITE_CLASS
#define SPRITE_CLASS

#include <iostream>

#define INCLUDE_SDL_IMAGE
#include "engine/SDL_include.h"

#include "engine/Component.h"
#include "util/Timer.h"

#define SPRITE_TYPE "Sprite"

using namespace std;

class Sprite : public Component {

public:
    explicit Sprite(GameObject& associated);
    explicit Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);

    ~Sprite() override;

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    SDL_Rect GetClip() const;
    int GetSpriteWidth();
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    void Render(float x, float y);
    bool Is(string type) override;

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();

    int GetCurrentFrame() const;

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);

    bool IsVisible();
    void SetVisible(bool visible);

private:
    shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;

    string currentSprite;

    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;

    Timer selfDestructCount;
    float secondsToSelfDestruct;

    bool isVisible;

};


#endif //SRC_SPRITE_H
