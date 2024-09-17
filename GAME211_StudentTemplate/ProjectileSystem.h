#pragma once
#include "Vector.h"
#include <thread>
#include <shared_mutex>
#include "DLinkedList.h"
#include "VMath.h"
#include "Enemy.h"
#include <vector>

class GameManager;

class ProjectileSystem : public Body
{

public:

	/// <summary>
	/// The system that controles and updates the projectles.
	/// it contains the position, travel direction, speed and peirce
	/// </summary>
	ProjectileSystem();

	/// <summary>
	/// The system that controles and updates the projectles.
	/// it contains the position, travel direction, speed and peirce
	/// </summary>
	/// <param name="projectile_">copys data from projectile</param>
	ProjectileSystem(const ProjectileSystem& projectile_);

	/// <summary>
	/// The system that controles and updates the projectles.
	/// it contains the position, travel direction, speed and peirce
	/// </summary>
	/// <param name="position_">position of the projectile in the world</param>
	/// <param name="direction_">direction that the projectile will travel in</param>
	/// <param name="speed_">speed that the projectile travels</param>
	/// <param name="pierce_">how many enimes that the projectile can damage</param>
	/// <param name="damage_">how much damage it deals on hit</param>
	/// <param name="collisonRadius_">the distance from the center position that is considered coliding</param>
	ProjectileSystem(MATH::Vec3 position_, MATH::Vec3 direction_, float speed_, int pierce_, float damage_, float collisonRadius_, float lifeSpan_, GameManager* game_);

	~ProjectileSystem();

	/// <summary>
	/// updates the projectiles position and checks for collision with the eneime;
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="eneimes"></param>
	/// <param name="projectiles_"></param>
	/// <param name="PLocation"></param>
	void Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, DLinkedList< std::shared_ptr<ProjectileSystem>>& projectiles_, int PLocation);

	/// <summary>
	/// updates the direction vector
	/// </summary>
	/// <param name="direction_">new direction vector</param>
	void updateDirection(MATH::Vec3 direction_);

	/// <summary>
	/// virtual copy constructor
	/// </summary>
	/// <returns>shared_ptr to a copy of this</returns>
	virtual std::shared_ptr<ProjectileSystem> Clone() const;

	/// <summary>
	/// gets the speed of the projectile
	/// </summary>
	/// <returns> the speed of the projectile</returns>
	float getProjectileSpeed() { return speed; };

	virtual bool OnCreate();
	virtual void Render(float scale);
	virtual void OnDestroy();

protected:

	/// <summary>
	/// pointer to the GameManager for rendering
	/// </summary>
	GameManager* game;

	/// <summary>
	/// the normalized vec3 which represent the direction that the projectle will travel
	/// </summary>
	MATH::Vec3 direction;

	/// <summary>
	/// speed of the projectile
	/// </summary>
	float speed;
	
	/// <summary>
	/// how many enimes can the projectile damage before being destroyed
	/// </summary>
	int pierce;

	/// <summary>
	/// how much damage the projectle deals
	/// </summary>
	float damage;

	/// <summary>
	/// the distance from the center position that is considered coliding
	/// </summary>
	float collisionRadius;

	/// <summary>
	/// how long the projectile stays alive
	/// </summary>
	float lifeSpan;

	/// <summary>
	/// total time the projectile is allive
	/// </summary>
	float totalTime = 0;

	std::vector<Enemy*> enemiesHit;
	int totalHit = 0;

	/// <summary>
	/// updates the current position of the projectile based on the projectile direction and speed * deltaTime
	/// </summary>
	/// <param name="deltaTime">time differance between position updates</param>
	void updatePosition(float deltaTime);

	/// <summary>
	/// checks to see if any enimes are withing collision range
	/// </summary>
	/// <param name="eneimes">Double linked list of all eneimes</param>
	void checkAllCollision(DLinkedList<std::shared_ptr<Enemy>>& liveEnemies);



};

