#include "Spawner.h"
#include "Enemy.h"
#include "GameManager.h"

Spawner::Spawner(float spawnDelay_)
{
	spawnDelay = spawnDelay_;
}

Spawner::~Spawner()
{
}

bool Spawner::OnCreate()
{
	return true;
}

void Spawner::Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies)
{
	spawnTimer += deltaTime;
	if (spawnTimer >= spawnDelay && leftToSpawn > 0)
	{
		std::shared_ptr<Enemy> newEnemy = currentlySpawning->Clone();
		liveEnemies.pushBack(newEnemy);
		spawnTimer = 0;
		leftToSpawn--;
	}
}

void Spawner::HandleEvents(const SDL_Event& event)
{
}

void Spawner::OnDestroy()
{
	if (leftToSpawn > 0)
	{
		currentlySpawning->OnDestroy();
	}
}

float Spawner::SetSpawnDelay(float newDelay)
{
	spawnDelay = newDelay;
	return spawnDelay;
}

void Spawner::SpawnEnemy(std::shared_ptr<Enemy> prototype, int numEnemies)
{
	currentlySpawning = prototype;
	leftToSpawn = numEnemies;
}
