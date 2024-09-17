#include "EnemyCircle.h"
#include "GameManager.h"

const float EnemyCircle::circleSpeed = 4;

EnemyCircle::EnemyCircle(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, circleSpeed, reward_, path_, game_)
{
}

EnemyCircle::EnemyCircle(const EnemyCircle& other) : Enemy(other)
{
}

EnemyCircle::~EnemyCircle()
{
}

bool EnemyCircle::OnCreate()
{
	image = IMG_Load("Enemy Assets/circle_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return FindNextTile();
}

std::shared_ptr<Enemy> EnemyCircle::Clone() const
{
	return std::make_shared<EnemyCircle>(*this);
}