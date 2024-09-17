#include "EnemyTriangle.h"
#include "GameManager.h"
#include "DLinkedList.h"

const float EnemyTriangle::triangleMinSpeed = 3.0f;
const float EnemyTriangle::triangleMaxSpeed = 15.0f;
const float EnemyTriangle::triangleAccel = 6.0f;

EnemyTriangle::EnemyTriangle(int maxHealth_, int reward_, DLinkedList<Vec2>& path_, GameManager* game_) :
	Enemy(maxHealth_, triangleMinSpeed, reward_, path_, game_)
{
	lastTarget = Vec3(path_[0].x, path_[0].y, 0.0f);
}

EnemyTriangle::EnemyTriangle(const EnemyTriangle& other) :
	Enemy(other)
{
	lastTarget = other.lastTarget;
}

EnemyTriangle::~EnemyTriangle()
{
}

bool EnemyTriangle::OnCreate()
{
	image = IMG_Load("Enemy Assets/triangle_enemy.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return FindNextTile();
}

void EnemyTriangle::Update(float deltaTime, DLinkedList<std::shared_ptr<Enemy>>& liveEnemies, int thisIndex)
{
	//if the target is within movement distance, don't run body's update to avoid overshooting it
	Vec3 targetDistance = target - pos;
	if (abs(targetDistance.x) + abs(targetDistance.y) < triangleMinSpeed * deltaTime)
	{
		pos = target;
		if (!FindNextTile())
		{
			game->LoseLives(currentHealth);
			liveEnemies.killNode(thisIndex);
		}
	}
	else
	{
		if (VMath::mag(targetDistance) <= VMath::mag(lastTarget - pos) &&
			(VMath::mag(accel) == 0.0f ||
			(VMath::normalize(accel).x == VMath::normalize(vel).x &&
			VMath::normalize(accel).y == VMath::normalize(vel).y)))
		{
			accel = -VMath::normalize(targetDistance) * triangleAccel;
		}


		Body::Update(deltaTime);
		
		if (VMath::mag(vel) > triangleMaxSpeed)
		{
			vel = VMath::normalize(vel) * triangleMaxSpeed;
			accel = Vec3();
		}
	}
}

std::shared_ptr<Enemy> EnemyTriangle::Clone() const
{
	return std::make_shared<EnemyTriangle>(*this);
}

bool EnemyTriangle::FindNextTile()
{
	//search path for current tile, then set next as target
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i].x == target.x && path[i].y == target.y)
		{
			if (i + 1 == path.size())
			{
				return false;
			}
			else {
				lastTarget = target;
				target = Vec3(path[i + 1].x, path[i + 1].y, 0);
				vel = VMath::normalize(target - pos) * triangleMinSpeed;
				accel = VMath::normalize(target - pos) * triangleAccel;

				return true;
			}
		}
	}
	return false;
}
