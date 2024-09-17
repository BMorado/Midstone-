#pragma once
#include "Enemy.h"

class EnemyStar : public Enemy
{
	//movement speed of star enemies
	static const float starSpeed;
	
	//how long a star enemy will be invulnerable for
	static const float invulnLength;
	float invulnTimer;
	bool isInvulnerable;

	//counter for transparent blink to show invulnerability
	int blinkCounter;
	//how many frames the blink takes
	static const int blinkInterval;

public:
	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	EnemyStar(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	EnemyStar(const EnemyStar& other);

	//destructor
	~EnemyStar();

	bool OnCreate() override;
	void Render(float scale = 1.0f) override;
	void Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, 
		int thisIndex) override;

	int TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex) override;

	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	std::shared_ptr<Enemy> Clone() const override;
};