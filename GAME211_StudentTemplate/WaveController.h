#pragma once
#include "DLinkedList.h"
#include <memory>
#include "Wave.h"

class Enemy;
class Spawner;

class WaveController 
{
	DLinkedList<std::shared_ptr<Wave>> waveQueue;

	std::shared_ptr<Spawner> spawner;
	std::shared_ptr<Enemy> currentEnemy;

	float breakTimer;
	const float interwaveBreakLength = 10.0f;

public:
	WaveController();
	~WaveController();

	void AddWave(std::shared_ptr<Enemy> enemyToSpawn, int numCopies);
	void AddWave(std::shared_ptr<Wave> wave);

	bool OnCreate();
	void Update(const float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies);
	void OnDestroy();

	void skipBreak();
	bool isSpawnerSpawning();
	bool hasFinished();
};
