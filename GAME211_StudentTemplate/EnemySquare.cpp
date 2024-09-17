#include "EnemySquare.h"
#include "GameManager.h"
#include "DLinkedList.h"
#include "EnemyMiniSquare.h"

const float EnemySquare::squareSpeed = 2;

EnemySquare::EnemySquare(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, squareSpeed, reward_, path_, game_)
{
	miniSquareToSpawn = std::make_shared<EnemyMiniSquare>(maxHealth_, reward_, path_, game_);
}

EnemySquare::EnemySquare(const EnemySquare& other) : 
	Enemy(other), miniSquareToSpawn{other.miniSquareToSpawn}
{
}

EnemySquare::~EnemySquare()
{
}

bool EnemySquare::OnCreate()
{
	image = IMG_Load("Enemy Assets/square_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	miniSquareToSpawn->OnCreate();
	return FindNextTile();
}

void EnemySquare::OnDestroy()
{
	miniSquareToSpawn->OnDestroy();
	Enemy::OnDestroy();
}

int EnemySquare::TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	currentHealth -= amount;
	if (currentHealth <= 0)
	{
		game->AddMoney(reward);
		if (thisIndex != liveEnemies.size() - 1)
		{
			liveEnemies.insert(thisIndex+1, std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(0.3f, 0.3f, 0)));
			liveEnemies.insert(thisIndex+1, std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(0.3f, -0.3f, 0)));
			liveEnemies.insert(thisIndex+1, std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(-0.3f, 0.3f, 0)));
			liveEnemies.insert(thisIndex+1, std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(-0.3f, -0.3f, 0)));
		}
		else
		{
			liveEnemies.pushBack(std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(0.3f, 0.3f, 0)));
			liveEnemies.pushBack(std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(0.3f, -0.3f, 0)));
			liveEnemies.pushBack(std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(-0.3f, 0.3f, 0)));
			liveEnemies.pushBack(std::make_shared<EnemyMiniSquare>(*miniSquareToSpawn, pos, target, Vec3(-0.3f, -0.3f, 0)));
		}
		liveEnemies.killNode(thisIndex);
	}
	return currentHealth;
}

std::shared_ptr<Enemy> EnemySquare::Clone() const
{
	return std::make_shared<EnemySquare>(*this);
}