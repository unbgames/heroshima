//
// Created by edgar on 22/03/18.
//

#include "../include/Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0)  {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect Rect::SumVec2(Vec2 v) {
    return {x + v.x, y + v.y, w, h};
}

Rect Rect::SubVec2(Vec2 v) {
    return {x - v.x, y - v.y, w, h};
}

Rect Rect::MulVec2(Vec2 v) {
    return {x, y, w * v.x, h * v.y};
}

Vec2 Rect::GetCenter() {
    return {x + (w/2), y + (h/2)};
}

Vec2 Rect::GetPos() {
    return {x , y};
}

void Rect::SetPos(Vec2 v) {
    x = v.x;
    y = v.x;
}

float Rect::DistRecs(Rect r) {
    Vec2 v = this->GetCenter();
    return v.Dist(r.GetCenter());
}

float Rect::DistVec2(Vec2 v) {
    return this->GetCenter().Dist(v);
}

bool Rect::Contains(Vec2 v) {
    return (v.x < (x + w) && v.x >= x) && (v.y < (y + h) && v.y >= y);
}

string Rect::toString() {
    char buffer [50];
    sprintf (buffer, "(%.2f, %.2f, %.2f, %.2f)\n", x, y, w, h);
    return buffer;
}

Rect Rect::operator+(Vec2 offset) {
    return SumVec2(offset);
}

Rect Rect::operator+=(Vec2 v) {
    return *this = SumVec2(v);
}

Rect Rect::operator-(Vec2 offset) {
    return SubVec2(offset);
}

Rect Rect::operator-=(Vec2 v) {
    return *this = SubVec2(v);
}

Rect Rect::operator*(Vec2 scale) {
    return MulVec2(scale);
}

Rect Rect::operator*=(Vec2 v) {
    return *this = MulVec2(v);
}

