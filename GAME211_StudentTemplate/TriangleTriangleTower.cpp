#include "TriangleTriangleTower.h"
#include <memory>

// Defualt Constructor
TriangleTriangleTower::TriangleTriangleTower() : TowerSystem()
{
	projectile = std::make_shared<TriangleTriangleProjectile>();
}

// Constructor taking position, fire rate and range
TriangleTriangleTower::TriangleTriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_)
{
	pos = pos_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<TriangleTriangleProjectile>(pos, MATH::Vec3(1, 0, 0), 20, 999, 3, 1, 10, game);
}
// Constructor taking position (seperated in x, y, z position), fire rate and range
TriangleTriangleTower::TriangleTriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_)
{
	pos.x = x_;
	pos.y = y_;
	pos.z = z_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<TriangleTriangleProjectile>(pos, MATH::Vec3(1, 0, 0), 20, 999, 3, 1, 10, game);
}

bool TriangleTriangleTower::OnCreate()
{
	image = IMG_Load("Tower Assets/triangle_triangle.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return projectile->OnCreate();
}
