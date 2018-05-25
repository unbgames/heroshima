//
// Created by edgar on 25/05/18.
//

#include <Weapons.h>

Gun *Weapons::pistol = new Gun(GunType::PISTOL, 20, -1 /*for infinite ammo*/, 0.5f,
        Sprites("img/tarma_superior_repouso.png", 10, 4, 0.5f),
        Sprites("img/tarma_superior_andando.png", 30, 12, 0.4f),
        Sprites("img/tarma_superior_atirando.png", 30, 10, 0.4f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));


Gun *Weapons::heavy = new Gun(GunType::HEAVY, 50, 100, 0.01f,
        Sprites("img/tarma_heavy_rest.png", 20, 4, 0.5f),
        Sprites("img/tarma_heavy_walk.png", 30, 12, 0.4f),
        Sprites("img/tarma_heavy_shoot.png", 38, 4, 0.4f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));

