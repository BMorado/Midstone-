#pragma once
#include "TowerSystem.h"
#include "TriangleTriangleProjectile.h"
#include "GameManager.h"

class TriangleTriangleTower : public TowerSystem
{
public:

    // Defualt Constructor
    TriangleTriangleTower();

    // Constructor taking position, fire rate and range
    TriangleTriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

    // Constructor taking position (seperated in x, y, z position), fire rate and range
    TriangleTriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

    bool OnCreate() override;

};
