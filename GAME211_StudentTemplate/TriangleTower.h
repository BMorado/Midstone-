#pragma once
#include "TowerSystem.h"
#include "GameManager.h"
#include "TriangleProjectiles.h"

class TriangleTower :public TowerSystem
{

public:


	/// <summary>
	/// default constructor for the tower
	/// </summary>
	TriangleTower();

	/// <summary>
	/// Constructor for the tower
	/// </summary>
	/// <param name="pos_"> Where the tower is locatied in the world</param>
	/// <param name="fireRate_"> How offten the tower can shoot</param>
	/// <param name="range_"> The maximum distance from the tower that it will fire</param>
	/// <param name="game_"></param>
	TriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_);

	/// <summary>
	/// Constructor for the tower
	/// </summary>
	/// <param name="x_"> the x location of the tower</param>
	/// <param name="y_"> the y location of the tower</param>
	/// <param name="z_"> the z location of the tower</param>
	/// <param name="fireRate_"> how offten the tower can shoot</param>
	/// <param name="range_"> the maximum distance from the tower that is will fire</param>
	/// <param name="game_"></param>
	TriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_);

	
	bool OnCreate() override;

protected:

	// Connects the circle projectile to the tower
	ProjectileSystem triangleProjectile;


};

