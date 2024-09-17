#pragma once
#include "ProjectileSystem.h"

class CircleProjectile : public ProjectileSystem
{
public:

	// Default Constructor
	CircleProjectile();

	// Constructor taking position, direction, speed, peirce, damage, collision radius, and life span
	CircleProjectile(MATH::Vec3 position_, MATH::Vec3 direction_,
		float speed_, float pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_);

	//copy constructor
	CircleProjectile(CircleProjectile& other);

	//virtual copy constructor
	std::shared_ptr<ProjectileSystem> Clone();

	bool OnCreate() override;
};

