//
// Created by edgar on 25/05/18.
//

#ifndef GUN_H
#define GUN_H

#include <string>
#include "Structs.h"

using std::string;

class Gun {
public:

    Gun(int damage, int ammo, float cooldownTime, Sprites spriteRest, Sprites spriteWalk,
        Sprites spriteShoot, Projectile projectile);

    Gun();

    int getDamage() const;
    int getAmmo() const;
    void setAmmo(int ammo);
    int getFull() const;
    float getCooldownTime() const;
    void decrementAmmo();

    const Sprites &getSpriteRest() const;
    const Sprites &getSpriteWalk() const;
    const Sprites &getSpriteShoot() const;

    const Projectile &getProjectile() const;

private:
    int damage;
    int ammo;

private:
    int full;

private:
    float cooldownTime;

    Sprites rest, walk, shoot;
    Projectile projectile;

};


#endif //SRC_GUN_H
