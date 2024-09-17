#pragma once
#include "TowerSystem.h"
#include "CircleCircleProjectile.h"
#include "GameManager.h"

class CircleCircleTower : public TowerSystem
{
public:

    // Defualt Constructor
    CircleCircleTower();

    // Constructor taking position, fire rate and range
    CircleCircleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

    // Constructor taking position (seperated in x, y, z position), fire rate and range
    CircleCircleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

    bool OnCreate() override;

};
