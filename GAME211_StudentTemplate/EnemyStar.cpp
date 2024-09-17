#include "EnemyStar.h"
#include "GameManager.h"

const float EnemyStar::starSpeed = 4;
const float EnemyStar::invulnLength = 1.0f;
const int EnemyStar::blinkInterval = 12;

EnemyStar::EnemyStar(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, starSpeed, reward_, path_, game_)
{
	isInvulnerable = false;
	invulnTimer = 0.0f;
	blinkCounter = 0;
}

EnemyStar::EnemyStar(const EnemyStar& other) : Enemy(other),
	isInvulnerable(other.isInvulnerable), invulnTimer(other.invulnTimer), 
	blinkCounter(other.blinkCounter)
{
}

EnemyStar::~EnemyStar()
{
}

bool EnemyStar::OnCreate()
{
	image = IMG_Load("Enemy Assets/star_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return FindNextTile();
}

void EnemyStar::Render(float scale)
{
	if (isInvulnerable)
	{
		blinkCounter++;
		if (blinkCounter <= blinkInterval)
			Enemy::Render(scale);
		else
		{
			if (blinkCounter == blinkInterval * 2)
				blinkCounter = 0;
		}
	}
	else
		Enemy::Render(scale);
}

void EnemyStar::Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	Enemy::Update(deltaTime, liveEnemies, thisIndex);
	if (isInvulnerable && invulnTimer < invulnLength)
	{
		invulnTimer += deltaTime;
		if (invulnTimer >= invulnLength)
			isInvulnerable = false;
	}
}

int EnemyStar::TakeDamage(int amount, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	if (!isInvulnerable)
	{
		isInvulnerable = true;
		invulnTimer = 0.0f;
		return Enemy::TakeDamage(amount, liveEnemies, thisIndex);
	}
	else return 0;
}

std::shared_ptr<Enemy> EnemyStar::Clone() const
{
	return std::make_shared<EnemyStar>(*this);
}
