#pragma once
#include "Enemy.h"

class EnemyMiniSquare;

class EnemySquare : public Enemy
{
	static const float squareSpeed;

	std::shared_ptr<EnemyMiniSquare> miniSquareToSpawn;

public:
	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	EnemySquare(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	EnemySquare(const EnemySquare& other);

	//destructor
	~EnemySquare();

	bool OnCreate() override;
	void OnDestroy() override;

	/// <summary>
	/// Applies damage from source to self
	/// </summary>
	/// <param name="amount"> Amount of damage dealt </param>
	/// <param name="source"> The projectile that dealt the damage </param>
	/// <returns> Remaining health after damage is taken </returns>
	int TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex) override;

	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	std::shared_ptr<Enemy> Clone() const override;
};