#pragma once

#include "Body.h"
#include <memory>

class ProjectileSystem;

template <typename T>
class DLinkedList;

class Enemy : public Body, public std::enable_shared_from_this<Enemy> {
	
protected:
	int maxHealth;
	int currentHealth;
	float moveSpeed;
	int reward; //how many bytes are given on kill
	Vec3 target; //where the enemy is currently moving to
	DLinkedList<Vec2>& path; //a list of the corner tiles that define the enemy path

	class GameManager* game;

public:
	

	/// <summary>
	/// Constructor with parameters
	/// </summary>
	/// <param name="maxHealth_"> Initial health for the enemy </param>
	/// <param name="moveSpeed_"> Base movement speed for the enemy </param>
	/// <param name="reward_"> How many bytes are given when the enemy is killed </param>
	/// <param name="path_"> The path along which the enemy will travel </param>
	/// <param name="game_"> GameManager to communicate with </param>
	Enemy(int maxHealth_, float moveSpeed_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_);

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="other">Enemy to copy</param>
	Enemy(const Enemy& other);

	//destructor
	virtual ~Enemy();

	virtual bool OnCreate();
	virtual void Render(float scale = 1.0f);
	virtual void HandleEvents(const SDL_Event& event);
	virtual void Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex);
	virtual void OnDestroy();
	virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }

	/// <returns> currentHealth </returns>
	int GetCurrentHealth() { return currentHealth; }
	
	/// <returns> reward </returns>
	int GetReward() { return reward; }

	/// <summary>
	/// Applies damage from source to self
	/// </summary>
	/// <param name="amount"> Amount of damage dealt </param>
	/// <param name="source"> The projectile that dealt the damage </param>
	/// <returns> Remaining health after damage is taken </returns>
	virtual int TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex);

	/// <summary>
	/// Virtual copy constructor
	/// </summary>
	/// <returns>A shared pointer to a new copy of this enemy</returns>
	virtual std::shared_ptr<Enemy> Clone() const;

protected:

	/// <summary>
	/// finds the next target tile along the path to move towards
	/// </summary>
	virtual bool FindNextTile();

};