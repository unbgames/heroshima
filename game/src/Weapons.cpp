//
// Created by edgar on 25/05/18.
//

#include <Weapons.h>

Gun *Weapons::pistol = new Gun(20, -1 /*for infinite ammo*/, 0.5f,
                               StaticSprite("img/tarma_superior_repouso.png", 4, 0.3f, 10),
                               StaticSprite("img/tarma_superior_andando.png", 12, 1.0f, 30),
                               StaticSprite("img/tarma_superior_atirando.png", 10, 0.01f, 30),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));


Gun *Weapons::heavy = new Gun(50, 300, 0.1f,
                              StaticSprite("img/tarma_heavy_rest.png", 4, 0.3f, 20),
                              StaticSprite("img/tarma_heavy_walk.png", 12, 1.0f, 30),
                              StaticSprite("img/tarma_heavy_shoot.png", 4, 0.02f, 38),
        Projectile("img/minionbullet2.png", 700, 3, 0.01f));

