#pragma once
#include "Vector.h"
#include <thread>
#include <shared_mutex>

#include "DLinkedList.h"
#include "ProjectileSystem.h"

class GameManager;

class TowerSystem : public Body
{

public:
	
	//constuctors

	/// <summary>
	/// A universal template which containes the location, fire rate, range of the tower and a the projectile.
	///  it also has a basic update function which will automaticly locate an enime and spawn a new projectile
	/// </summary>
	TowerSystem();

	/// <summary>
	/// A universal template which containes the location, fire rate, range of the tower and a the projectile.
	///  it also has a basic update function which will automaticly locate an enime and spawn a new projectile
	/// </summary>
	/// <param name="x_">the x location of the tower</param>
	/// <param name="y_">the y location of the tower</param>
	/// <param name="z_">the z location of the tower</param>
	/// <param name="fireRate_">how often the toweer can fire</param>
	/// <param name="range_">the distance of which the tower can fire</param>
	TowerSystem(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

	/// <summary>
	///  A universal template which containes the location, fire rate, range of the tower and a the projectile.
	///  it also has a basic update function which will automaticly locate an enime and spawn a new projectile
	/// </summary>
	/// <param name="pos_">postion of the tower</param>
	/// <param name="fireRate_">how oftern the tower cn fire</param>
	/// <param name="range_">the distance of which the tower can fire</param>
	TowerSystem(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

	/// <summary>
	/// A universal template which containes the location, fire rate, range of the tower and a the projectile.
	///  it also has a basic update function which will automaticly locate an enime and spawn a new projectile
	/// </summary>
	/// <param name="tower_">copy a tower contense</param>
	TowerSystem(const TowerSystem& tower_);

	/// <summary>
	/// updates the tower based on the delta time.
	/// this includes cheaking if a projectile is to be fired
	/// </summary>
	/// <param name="deltaTime">The time between each update</param>
	/// <param name="enemies">the vector that all eneimes are stored</param>
	/// <param name="projectiles">the vector all projectiles are stored</param>
	void update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles);

	/// <summary>
	/// updates the tower based on the delta time.
	/// this includes cheaking if a projectile is to be fired
	/// 
	/// This update overload is designed to be multiThreaded
	/// </summary>
	/// <param name="deltaTime">The time between each update</param>
	/// <param name="enemies">the vector that all eneimes are stored</param>
	/// <param name="projectiles">the vector all projectiles are stored</param>
	void update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles, std::shared_mutex& mutex_);

	virtual bool OnCreate();
	virtual void Render(float scale);
	virtual void OnDestroy();

protected:

	//pointer to GameManager for rendering
	GameManager* game;

	//how offten the tower can fire
	float fireRate;

	//how far can the tower shoot
	float range;

	//total deltaTime;
	float currentTime = 0;

	std::shared_ptr<ProjectileSystem> projectile;

	/// <summary>
	///  this will go through the vector of eneimes and see if any are in range
	/// if they are in range spawn a new projectle that is added to projectile vector with the corret direction vector
	/// </summary>
	/// <param name="enemies">The vector where all spawned enimes are stored</param>
	/// <param name="projectiles">the vector where all projectles are stored</param>
	/// <returns>returns true if it shot a projectile, flase if it didnt fire</returns>
	bool fireProjectile(DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles);


	bool fireProjectile(DLinkedList<std::shared_ptr<Enemy>>& enemies, DLinkedList<std::shared_ptr<ProjectileSystem>>& projectiles,std::shared_mutex& mutex_);

	

};

