#include "TriangleTower.h"

TriangleTower::TriangleTower()
{
	projectile = std::make_shared<TriangleProjectiles>();
}

TriangleTower::TriangleTower(MATH::Vec3 pos_, float fireRate_, float range_, GameManager* game_)
{
	pos = pos_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<TriangleProjectiles>(pos, MATH::Vec3(1, 0, 0), 20, 5, 2, 1, 10, game);
}

TriangleTower::TriangleTower(float x_, float y_, float z_, float fireRate_, float range_, GameManager* game_)
{
	pos.x = x_;
	pos.y = y_;
	pos.z = z_;
	fireRate = fireRate_;
	range = range_;
	game = game_;
	projectile = std::make_shared<TriangleProjectiles>(pos, MATH::Vec3(1, 0, 0), 20, 5, 2, 1, 10, game);
}

bool TriangleTower::OnCreate()
{
	image = IMG_Load("Tower Assets/triangle_tower.png");
	SDL_Renderer* renderer = game->getRenderer();
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	return projectile->OnCreate();
}
