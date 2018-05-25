//
// Created by edgar on 25/05/18.
//

#ifndef GUN_H
#define GUN_H

#include <string>

using std::string;

typedef struct Sprites{
    string sprite;
    int offset;
    int frameCount;
    float frameTime;

    Sprites(string sprite, int offset, int frameCount, float frameTime);
    Sprites();
};

typedef struct Projectile{
    string sprite;
    float speed;
    int frameCount;
    float frameTime;

    Projectile(string sprite, float speed, int frameCount, float frameTime);
    Projectile();
};

class Gun {
public:

    Gun(int damage, int ammo, float cooldownTime, const Sprites &spriteRest, const Sprites &spriteWalk,
        const Sprites &spriteShoot, const Projectile &projectile);

    Gun();

    int getDamage() const;
    int getAmmo() const;
    float getCooldownTime() const;
    void decrementAmmo();

    const Sprites &getSpriteRest() const;
    const Sprites &getSpriteWalk() const;
    const Sprites &getSpriteShoot() const;

    const Projectile &getProjectile() const;

private:
    int damage;
    int ammo;
    float cooldownTime;

    Sprites spriteRest, spriteWalk, spriteShoot;
    Projectile projectile;

};


#endif //SRC_GUN_H
