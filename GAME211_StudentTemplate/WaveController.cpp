#include "WaveController.h"
#include "Spawner.h"
#include "Wave.h"
#include "Enemy.h"

WaveController::WaveController() : breakTimer{ 0.0f }, spawner{ std::make_shared<Spawner>() }, waveQueue{}
{
}

WaveController::~WaveController()
{
}

void WaveController::AddWave(std::shared_ptr<Enemy> enemyToSpawn, int numCopies)
{
	waveQueue.pushBack(std::make_shared<Wave>(enemyToSpawn, numCopies));
}

void WaveController::AddWave(std::shared_ptr<Wave> wave)
{
	waveQueue.pushBack(wave);
}

bool WaveController::OnCreate()
{
	return spawner->OnCreate();
}

void WaveController::Update(const float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies)
{
	if (spawner->IsSpawning())
	{
		spawner->Update(deltaTime, liveEnemies);
	}
	else if (liveEnemies.size() == 0)
	{
		if (currentEnemy) {
			currentEnemy->OnDestroy();
			currentEnemy = nullptr;
		}

		breakTimer += deltaTime;
		if (breakTimer >= interwaveBreakLength)
		{
			breakTimer = 0.0f;
			std::shared_ptr<Wave> newWave = waveQueue.popFront();
			if (newWave) 
			{
				currentEnemy = newWave->waveEnemy;
				currentEnemy->OnCreate();
				spawner->SpawnEnemy(newWave->waveEnemy, newWave->numInWave);
			}
		}
	}
}

void WaveController::OnDestroy()
{
	spawner->OnDestroy();
}

void WaveController::skipBreak()
{
	if (!spawner->IsSpawning())
	{
		breakTimer = interwaveBreakLength;
	}
}

bool WaveController::isSpawnerSpawning()
{
	return spawner->IsSpawning();
}

bool WaveController::hasFinished()
{
	return waveQueue.size() == 0 && !spawner->IsSpawning();
}
