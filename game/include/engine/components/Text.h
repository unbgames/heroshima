//
// Created by edgar on 12/05/18.
//

#ifndef SRC_TEXT_H
#define SRC_TEXT_H


#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "engine/SDL_include.h"
#include "engine/Component.h"

#define TEXT_TYPE "Text"

class Text : public Component{
public:
    enum TextStyle{SOLID, SHADED, BLENDED};
    Text(GameObject &associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
    virtual ~Text();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void SetText(string text);
    const string &GetText() const;
    void SetColor(SDL_Color color);
    const SDL_Color &GetColor() const;
    void SetAlpha(Uint8 alpha);
    void SetStyle(TextStyle style);
    void SetFontFile(string fontFile);
    void SetFontSize(int fontSize);


private:
    void RemakeTexture();

    shared_ptr<TTF_Font> font;
    SDL_Texture* texture;

    string text;

private:
    TextStyle style;
    string fontFile;
    int fontSize;
    SDL_Color color;

};


#endif //SRC_TEXT_H
