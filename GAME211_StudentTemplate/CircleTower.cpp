#include "CircleTower.h"
#include <memory>

// Defualt Constructor
CircleTower::CircleTower() : TowerSystem()
{
	projectile = std::make_shared<CircleProjectile>();
}

// Constructor taking position, fire rate and range
CircleTower::CircleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_)
{
	pos = pos_;
	fireRate = fireRate_;
	range = range_;
    game = game_;
	projectile = std::make_shared<CircleProjectile>(pos, MATH::Vec3(1, 0, 0), 10, 2, 1, 1, 10, game);
}
// Constructor taking position (seperated in x, y, z position), fire rate and range
CircleTower::CircleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_)
{
	pos.x = x_;
	pos.y = y_;
	pos.z = z_;
	fireRate = fireRate_;
	range = range_;
    game = game_;
	projectile = std::make_shared<CircleProjectile>(pos, MATH::Vec3(1, 0, 0), 10, 2, 1, 1, 10, game);
}

bool CircleTower::OnCreate()
{
	image = IMG_Load("Tower Assets/circle_tower.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return projectile->OnCreate();
}
