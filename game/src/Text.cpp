//
// Created by edgar on 12/05/18.
//

#include <Game.h>
#include <Camera.h>

#include <Resources.h>
#include "Text.h"

Text::Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated),
                                                                                                                   fontFile(move(fontFile)) {

    this->fontSize = fontSize;
    this->style = style;
    this->text = move(text);
    this->color = color;
    this->texture = nullptr;
    RemakeTexture();
}

Text::~Text() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {}

void Text::Render() {
    auto box = associated.box;
    auto renderPos = (Vec2(box.x, box.y) - Camera::pos);
    SDL_Rect clipRect = { 0, 0, (int) box.w, (int) box.h };
    SDL_Rect dstRect = { (int)(renderPos.x), (int)(renderPos.y), clipRect.w, clipRect.h };
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),  texture,  &clipRect,  &dstRect,  associated.angleDeg,  nullptr,  SDL_FLIP_NONE);
}

bool Text::Is(string type) {
    return type == TEXT_TYPE;
}

void Text::setText(string text) {
    Text::text = move(text);
    RemakeTexture();
}

void Text::setColor(SDL_Color color) {
    Text::color = color;
    RemakeTexture();
}

void Text::setStyle(TextStyle style) {
    Text::style = style;
    RemakeTexture();
}

void Text::setFontFile(string fontFile) {
    Text::fontFile = move(fontFile);
}

void Text::setFontSize(int fontSize) {
    Text::fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    font = Resources::GetFont(fontFile, fontSize);

    SDL_Surface *surface = nullptr;
    if(style == TextStyle::SOLID) surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
    else if(style == TextStyle::SHADED) surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, { 0, 0, 0, 255 });
    else if(style == TextStyle::BLENDED) surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_SetTextureAlphaMod(texture, color.a);

    if(surface) {
        associated.box.w = surface->w;
        associated.box.h = surface->h;
    }

    SDL_FreeSurface(surface);

}

const SDL_Color &Text::getColor() const {
    return color;
}

const string &Text::getText() const {
    return text;
}

void Text::SetAlpha(Uint8 alpha) {
    color = {color.r, color.g, color.b, alpha};
    RemakeTexture();
}
