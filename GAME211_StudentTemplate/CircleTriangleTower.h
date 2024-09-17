#pragma once
#include "TowerSystem.h"
#include "CircleTriangleProjectile.h"
#include "GameManager.h"

class CircleTriangleTower : public TowerSystem
{
public:

    // Defualt Constructor
    CircleTriangleTower();

    // Constructor taking position, fire rate and range
    CircleTriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

    // Constructor taking position (seperated in x, y, z position), fire rate and range
    CircleTriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

    bool OnCreate() override;

};
