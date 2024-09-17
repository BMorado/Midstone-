#pragma once
#include "ProjectileSystem.h"

class CircleCircleProjectile : public ProjectileSystem
{
public:

	// Default Constructor
	CircleCircleProjectile();

	// Constructor taking position, direction, speed, peirce, damage, collision radius, and life span
	CircleCircleProjectile(MATH::Vec3 position_, MATH::Vec3 direction_,
		float speed_, float pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_);

	//copy constructor
	CircleCircleProjectile(CircleCircleProjectile& other);

	//virtual copy constructor
	std::shared_ptr<ProjectileSystem> Clone();

	bool OnCreate() override;
};
