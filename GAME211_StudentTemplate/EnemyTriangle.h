#pragma once
#include "Enemy.h"

class EnemyTriangle : public Enemy
{
	static const float triangleMinSpeed;
	static const float triangleMaxSpeed;
	static const float triangleAccel;

	Vec3 lastTarget;

public:
	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	EnemyTriangle(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	EnemyTriangle(const EnemyTriangle& other);

	//destructor
	~EnemyTriangle();

	bool OnCreate() override;
	void Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex) override;
	
	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	std::shared_ptr<Enemy> Clone() const override;

private:

	/// <summary>
	/// finds the next target tile along the path to move towards
	/// </summary>
	/// <returns>whether or not a tile was found</returns>
	bool FindNextTile() override;
};