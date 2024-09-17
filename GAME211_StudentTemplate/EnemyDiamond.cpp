#include "EnemyDiamond.h"
#include "GameManager.h"
#include "DLinkedList.h"

const float EnemyDiamond::diamondSpeed = 3;

EnemyDiamond::EnemyDiamond(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, diamondSpeed, reward_, path_, game_)
{
}

EnemyDiamond::EnemyDiamond(const EnemyDiamond& other) : Enemy(other)
{
}

EnemyDiamond::~EnemyDiamond()
{
}

bool EnemyDiamond::OnCreate()
{
	image = IMG_Load("Enemy Assets/diamond_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return FindNextTile();
}

int EnemyDiamond::TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	currentHealth -= amount - 1;
	if (currentHealth <= 0)
	{
		game->AddMoney(reward);
		liveEnemies.killNode(thisIndex);
	}
	return currentHealth;
}

std::shared_ptr<Enemy> EnemyDiamond::Clone() const
{
	return std::make_shared<EnemyDiamond>(*this);
}
