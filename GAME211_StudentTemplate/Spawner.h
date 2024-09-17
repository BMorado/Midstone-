#pragma once

#include <SDL.h>
#include <memory>
#include "DLinkedList.h"

class Enemy;

class Spawner {
	float spawnDelay; //how much time elapses between spawns
	std::shared_ptr<Enemy> currentlySpawning = nullptr; //current enemy being spawned
	int leftToSpawn = 0; //how many more enemies will be spawned
	float spawnTimer = 0.0f; //how much time has elapsed since last spawn

public:
	Spawner(float spawnDelay_=0.75f);
	~Spawner();

	bool OnCreate();
	void Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies);
	void HandleEvents(const SDL_Event& event);
	void OnDestroy();

	float SetSpawnDelay(float newDelay);
	void SpawnEnemy(std::shared_ptr<Enemy> prototype, int numEnemies);

	bool IsSpawning() { return leftToSpawn > 0; }
};
