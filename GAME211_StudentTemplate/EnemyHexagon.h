#pragma once
#include "Enemy.h"

class EnemyHexagon : public Enemy
{
	static const float hexSpeed;

public:
	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	EnemyHexagon(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	EnemyHexagon(const EnemyHexagon& other);

	//destructor
	~EnemyHexagon();

	bool OnCreate() override;

	int TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex) override;

	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	std::shared_ptr<Enemy> Clone() const override;
};