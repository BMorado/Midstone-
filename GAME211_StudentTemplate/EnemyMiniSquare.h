#pragma once
#include "Enemy.h"

class EnemyMiniSquare : public Enemy
{
	static const float miniSquareSpeed;

	Vec3 offset;

public:
	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	EnemyMiniSquare(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	EnemyMiniSquare(const EnemyMiniSquare& other);

	/// <summary>
	/// copy constructor with position for spawning at a SquareEnemy's death
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	/// <param name="pos_">Initial postition for the enemy</param>
	/// <param name="target_">Initial target for the enemy</param>
	/// <param name="Offset_">Amount this enemy is offset from the path</param>
	EnemyMiniSquare(const EnemyMiniSquare& other, Vec3 pos_, Vec3 target_, Vec3 offset_);

	//destructor
	~EnemyMiniSquare();

	bool OnCreate() override;
	void Render(float scale = 1.0f);

	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	std::shared_ptr<Enemy> Clone() const override;

private:

	/// <summary>
	/// finds the next target tile along the path to move towards
	/// </summary>
	bool FindNextTile() override;
};