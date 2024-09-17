#pragma once
#include "TowerSystem.h"
#include "CircleProjectile.h"
#include "GameManager.h"

class CircleTower : public TowerSystem
{
public:

    // Defualt Constructor
    CircleTower();

    // Constructor taking position, fire rate and range
    CircleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

    // Constructor taking position (seperated in x, y, z position), fire rate and range
    CircleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

    bool OnCreate() override;

protected:
    // Connects the circle projectile to the tower
    ProjectileSystem circleProjectile = CircleProjectile();

};

