//
// Created by edgar on 16/03/18.
//

#define INCLUDE_SDL_IMAGE

#include "Resources.h"
#include "Camera.h"

#include <utility>
#include "Bullet.h"
#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) :
    Component(associated), texture(nullptr), scale(1, 1), selfDestructCount(*new Timer),
    secondsToSelfDestruct(0) {

    frameCount = 0;
    frameTime = 0;
    timeElapsed = 0;
    currentFrame = 0;
    currentSprite = "";
    isVisible = true;
}

Sprite::Sprite(GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct)
    : Component(associated), texture(nullptr),  scale(1, 1), selfDestructCount(*new Timer),
      secondsToSelfDestruct(secondsToSelfDestruct) {

    this->frameCount = frameCount;
    this->frameTime = frameTime;
    timeElapsed = 0;
    currentFrame = 0;
    currentSprite = "";
    isVisible = true;
    Open(move(file));
}

Sprite::~Sprite() {
//    Resources cuida da desalocagem
}

void Sprite::Open(string file) {

    // Se for o mesmo sprite não abre denovo o sprite
    if (texture != nullptr && currentSprite == file) {
        return;
    }

    currentSprite = file;
    texture = Resources::GetImage(move(file));
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    SetClip(0, 0, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x; clipRect.y = y;
    clipRect.h = h; clipRect.w = w;
}

SDL_Rect Sprite::GetClip() const {
    return clipRect;
}

void Sprite::Render() {
    Render((int)associated.box.x  - (int)Camera::pos.x, (int)associated.box.y - (int)Camera::pos.y);
}

void Sprite::Render(float x, float y) {
    SDL_Rect dst = { (int)x, (int)y, (int)(clipRect.w * scale.x), (int)(clipRect.h * scale.x) };
    auto flipType = associated.orientation == Orientation::LEFT ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if(isVisible){
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dst, associated.angleDeg, nullptr , flipType);
    }
//    SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dst);//debug
}

int Sprite::GetSpriteWidth() {
    return (int)(width * scale.x);
}

int Sprite::GetWidth() {
    return (int)(width * scale.x)/frameCount;
}

int Sprite::GetHeight() {
    return (int)(height * scale.y);
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt) {
    if(secondsToSelfDestruct > 0){
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() > secondsToSelfDestruct){
            associated.RequestDelete();
        }
    }

    timeElapsed += dt;
    if(timeElapsed >= frameTime){
        if(++currentFrame >= frameCount){
            currentFrame = 0;
        }
        SetFrame(currentFrame);
        timeElapsed = 0;
    }
}

bool Sprite::Is(string type) {
    return type == SPRITE_TYPE;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    auto &box = associated.box;
    if(scaleX != 0){
        scale.x = scaleX;
        box.w = width * scaleX;
        box.x = box.GetCenter().x - box.w/2;
    }

    if(scaleY != 0){
        scale.y = scaleY;
        box.h = height * scaleY;
        box.y = box.GetCenter().y - box.h/2;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::SetFrame(int frame) {
    this->currentFrame = frame;
    SetClip(frame * GetWidth(), 0, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount(int frameCount) {
    if (this->frameCount != frameCount) {
        this->frameCount = frameCount;
        currentFrame = 0;
        associated.box.w = GetWidth();
        SetClip(0, clipRect.y, GetWidth(), clipRect.h);
    }
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

int Sprite::GetCurrentFrame() const {
    return currentFrame;
}

bool Sprite::IsVisible() {
    return isVisible;
}

void Sprite::SetVisible(bool visible) {
    isVisible = visible;
}
