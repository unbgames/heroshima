//
// Created by edgar on 25/05/18.
//

#include <Weapons.h>

Gun *Weapons::pistol = new Gun(20, -1 /*for infinite ammo*/, 0.5f,
        Sprites("img/tarma_superior_repouso.png", 10, 4, 0.3f),
        Sprites("img/tarma_superior_andando.png", 30, 12, 1.0f),
        Sprites("img/tarma_superior_atirando.png", 30, 10, 0.01f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));


Gun *Weapons::heavy = new Gun(50, 50, 0.01f,
        Sprites("img/tarma_heavy_rest.png", 20, 4, 0.3f),
        Sprites("img/tarma_heavy_walk.png", 30, 12, 1.0f),
        Sprites("img/tarma_heavy_shoot.png", 38, 4, 0.02f),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));

