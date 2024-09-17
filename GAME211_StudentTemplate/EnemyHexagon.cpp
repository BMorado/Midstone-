#include "EnemyHexagon.h"
#include "GameManager.h"
#include "DLinkedList.h"

const float EnemyHexagon::hexSpeed = 5;

EnemyHexagon::EnemyHexagon(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, hexSpeed, reward_, path_, game_)
{
}

EnemyHexagon::EnemyHexagon(const EnemyHexagon& other) : Enemy(other)
{
}

EnemyHexagon::~EnemyHexagon()
{
}

bool EnemyHexagon::OnCreate()
{
	image = IMG_Load("Enemy Assets/hexagon_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return FindNextTile();
}

int EnemyHexagon::TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	currentHealth -= amount;
	if (currentHealth <= 0)
	{
		game->AddMoney(reward);
		liveEnemies.killNode(thisIndex);
	}
	return currentHealth;
}

std::shared_ptr<Enemy> EnemyHexagon::Clone() const
{
	return std::make_shared<EnemyHexagon>(*this);
}
