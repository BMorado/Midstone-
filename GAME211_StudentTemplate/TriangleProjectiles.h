#pragma once
#include "ProjectileSystem.h"
class TriangleProjectiles : public ProjectileSystem
{

public:

	/// <summary>
	/// default constructor
	/// </summary>
	TriangleProjectiles();

	/// <summary>
	/// contructor
	/// </summary>
	/// <param name="position_"> position of projectile</param>
	/// <param name="direction_"> the direction of travel of the projectile</param>
	/// <param name="speed_"> speed of the projectile</param>
	/// <param name="pierce_"> how many enimies that the projectile can damage</param>
	/// <param name="damage_"> how much damage the projectile deals</param>
	/// <param name="collisionRadius_"> how large the projectile is</param>
	/// <param name="lifeSpan_"> how long the projectile will last before destroying itself</param>
	/// <param name="game_"></param>
	TriangleProjectiles(MATH::Vec3 position_, MATH::Vec3 direction_,
		float speed_, float pierce_, float damage_, float collisionRadius_, float lifeSpan_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other"> the projectile to copy</param>
	TriangleProjectiles(TriangleProjectiles& other);

	/// <summary>
	/// virtual copy constructor
	/// </summary>
	/// <returns></returns>
	std::shared_ptr<ProjectileSystem> Clone();


	bool OnCreate() override;

};

