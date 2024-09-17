#include "CircleTriangleTower.h"
#include <memory>

// Defualt Constructor
CircleTriangleTower::CircleTriangleTower() : TowerSystem()
{
	projectile = std::make_shared<CircleTriangleProjectile>();
}

// Constructor taking position, fire rate and range
CircleTriangleTower::CircleTriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_)
{
	pos = pos_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<CircleTriangleProjectile>(pos, MATH::Vec3(1, 0, 0), 10, 8, 2, 1, 10, game);
}
// Constructor taking position (seperated in x, y, z position), fire rate and range
CircleTriangleTower::CircleTriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_)
{
	pos.x = x_;
	pos.y = y_;
	pos.z = z_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<CircleTriangleProjectile>(pos, MATH::Vec3(1, 0, 0), 10, 8, 2, 1, 10, game);
}

bool CircleTriangleTower::OnCreate()
{
	image = IMG_Load("Tower Assets/circle_triangle.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return projectile->OnCreate();
}
